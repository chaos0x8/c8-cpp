#include "c8-network/Pipe.hpp"
#include <gmock/gmock.h>

namespace C8::Network {
  using namespace testing;

  class TestPipe : public Test {
  public:
    Pipe sut;
  };

  TEST_F(TestPipe, shouldReadAndWrite) {
    sut.write("Hello world");
    ASSERT_THAT(sut.read(), Eq("Hello world"));
  }
} // namespace C8::Network
