#include "Error.hpp"
#include "Pipe.hpp"
#include <fstream>
#include <gmock/gmock.h>
#include <thread>

namespace NamedPipe {
  using namespace testing;
  using namespace std::string_literals;

  struct TestPipe : public Test {
    std::string name = tmpnam(nullptr);
    Pipe sut{name};
  };

  TEST_F(TestPipe, shouldRaiseWhenCannotCreate) {
    ASSERT_THROW(Pipe("/tmp/"s + name), Error);
  }

  TEST_F(TestPipe, shouldWriteLine) {
    auto t = std::thread([this] {
      File file = sut.openForWrite();
      file.write("Hello");
      file.write("World");
    });

    File file = sut.openForRead();
    ASSERT_THAT(file.read(), Eq("Hello"));
    ASSERT_THAT(file.read(), Eq("World"));

    t.join();
  }
} // namespace NamedPipe
