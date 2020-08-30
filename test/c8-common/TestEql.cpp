#include "c8-common/Eql.hpp"
#include <gmock/gmock.h>

namespace C8::Common {
  using namespace testing;

  TEST(TestEql, shouldFloatsBeEqual) {
    ASSERT_THAT(eql(2.0f, 2.f), Eq(true));
    ASSERT_THAT(eql(4.0, 4.0), Eq(true));
  }

  TEST(TestEql, shouldFloatBeNotEqual) {
    ASSERT_THAT(eql(2.0f, 2.1f), Eq(false));
    ASSERT_THAT(eql(3.0, 4.0), Eq(false));
  }
} // namespace C8::Common
