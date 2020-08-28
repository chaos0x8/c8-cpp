#include "c8-common/Format.hpp"
#include <gmock/gmock.h>

namespace C8::Common {
  using namespace testing;

  struct TestFormat : public Test {};

  TEST_F(TestFormat, shouldFormatNumer) {
    ASSERT_THAT(format("%d", 42), Eq("42"));
  }
} // namespace C8::Common
