#include "c8-common/errors/SystemError.hpp"
#include "c8-network/TcpIpClient.hpp"
#include "c8-network/TcpIpServer.hpp"
#include <future>
#include <gmock/gmock.h>

namespace C8::Network {
  using namespace testing;

  class TestTcpIpSockets : public Test {
  public:
    TestTcpIpSockets() {
      acceptResult =
        std::async(std::launch::async, [&] { return listener.accept(); });
    }

    TcpIpServer listener{LOCAL_HOST, PORT};
    std::future<TcpIpClient> acceptResult;

    static const std::string LOCAL_HOST;
    static const std::string PORT;
  };

  const std::string TestTcpIpSockets::LOCAL_HOST = "127.0.0.1";
  const std::string TestTcpIpSockets::PORT = "3042";

  TEST_F(TestTcpIpSockets, sendReceive) {
    TcpIpClient clientClientSide = TcpIpClient{LOCAL_HOST, PORT};
    clientClientSide.send("Hello world");

    TcpIpClient clientServerSide = acceptResult.get();
    ASSERT_THAT(clientServerSide.receive(), Eq("Hello world"));
  }

  TEST_F(TestTcpIpSockets, sendRecvStringWithSize) {
    TcpIpClient clientClientSide = TcpIpClient{LOCAL_HOST, PORT};
    clientClientSide.send("Hello world");

    TcpIpClient clientServerSide = acceptResult.get();
    ASSERT_THAT(clientServerSide.receive(3), Eq("Hel"));
  }

  TEST_F(TestTcpIpSockets, shoutdownClient) {
    TcpIpClient clientClientSide = TcpIpClient{LOCAL_HOST, PORT};
    TcpIpClient clientServerSide = acceptResult.get();

    clientServerSide.shutdown();

    ASSERT_THAT(clientClientSide.receive(), IsEmpty());
    ASSERT_THAT(clientServerSide.receive(), IsEmpty());
  }

  TEST_F(TestTcpIpSockets, shutdownListenerThrowsException) {
    TcpIpClient clientClientSide = TcpIpClient{LOCAL_HOST, PORT};
    TcpIpClient clientServerSide = acceptResult.get();

    ASSERT_THROW(listener.shutdown(), Common::Errors::SystemError);
  }

  TEST_F(TestTcpIpSockets, shouldCompareWithNativeHandler) {
    TcpIpClient clientClientSide = TcpIpClient{LOCAL_HOST, PORT};
    TcpIpClient clientServerSide = acceptResult.get();

    ASSERT_THAT(clientClientSide, Eq(clientClientSide.getNativeHandler()));
    ASSERT_THAT(clientClientSide, Ne(clientServerSide.getNativeHandler()));
  }

  struct TcpIpSockets_rawMessages_TestSuite : public TestTcpIpSockets {
    struct Message {
      bool operator==(const Message& other) const {
        return x == other.x and y == other.y;
      }

      int x;
      int y;
    };

    Message msg{7, 42};
    Message act{};
  };

  TEST_F(TcpIpSockets_rawMessages_TestSuite, sendReceive) {
    TcpIpClient clientClientSide = TcpIpClient{LOCAL_HOST, PORT};
    TcpIpClient clientServerSide = acceptResult.get();

    clientClientSide.send(&msg, sizeof(msg));

    ASSERT_THAT(clientServerSide.receive(&act, sizeof(act)), Eq(true));
    ASSERT_THAT(act, Eq(msg));
  }

  TEST_F(TcpIpSockets_rawMessages_TestSuite, shoutdownClient) {
    TcpIpClient clientClientSide = TcpIpClient{LOCAL_HOST, PORT};
    TcpIpClient clientServerSide = acceptResult.get();

    clientServerSide.shutdown();

    ASSERT_THAT(clientClientSide.receive(&act, sizeof(act)), Eq(false));
    ASSERT_THAT(clientServerSide.receive(&act, sizeof(act)), Eq(false));
  }
} // namespace C8::Network
