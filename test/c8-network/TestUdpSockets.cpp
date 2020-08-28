#include "c8-common/errors/SystemError.hpp"
#include "c8-network/UdpClient.hpp"
#include "c8-network/UdpServer.hpp"
#include <gmock/gmock.h>

namespace C8::Network {
  using namespace testing;

  class TestUdpSockets : public Test {
  public:
    UdpServer server{LOCAL_HOST, PORT};
    UdpClient client{LOCAL_HOST, PORT};

    static const std::string LOCAL_HOST;
    static const std::string PORT;
  };

  const std::string TestUdpSockets::LOCAL_HOST = "127.0.0.1";
  const std::string TestUdpSockets::PORT = "3042";

  TEST_F(TestUdpSockets, sendReceive) {
    client.send("Hello world");
    UdpMessage msg = server.receive();
    server.send(msg.clone("Hello back"));
    ASSERT_THAT(msg.data, Eq("Hello world"));
    ASSERT_THAT(client.receive(), Eq("Hello back"));

    UdpHost host = msg.getHost();
    ASSERT_THAT(host.name, Eq("localhost"));
    ASSERT_THAT(host.service, Not(IsEmpty()));
  }

  TEST_F(TestUdpSockets, shutdownClient) {
    client.shutdown();

    ASSERT_THAT(client.receive(), IsEmpty());
  }
} // namespace C8::Network
