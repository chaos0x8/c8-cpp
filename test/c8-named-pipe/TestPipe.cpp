#include "c8-common/errors/SystemError.hpp"
#include "c8-named-pipe/Pipe.hpp"
#include <fstream>
#include <gmock/gmock.h>
#include <thread>

namespace C8::NamedPipe {
  using namespace testing;
  using namespace std::string_literals;

  struct TestPipe : public Test {
    void TearDown() override {
      if (t.joinable()) {
        t.join();
      }
    }

    std::string name = tmpnam(nullptr);
    Pipe sut{name};
    std::thread t;
  };

  TEST_F(TestPipe, shouldRaiseWhenCannotCreate) {
    ASSERT_THROW(Pipe("/tmp/"s + name), Common::Errors::SystemError);
  }

  TEST_F(TestPipe, shouldWriteLine) {
    t = std::thread([this] {
      File file = sut.openForWrite();
      EXPECT_NO_THROW(file.write("Hello"));
      EXPECT_NO_THROW(file.write("World"));
    });

    File file = sut.openForRead();
    ASSERT_THAT(file.read(), Eq("Hello"));
    ASSERT_THAT(file.read(), Eq("World"));
  }
} // namespace C8::NamedPipe
