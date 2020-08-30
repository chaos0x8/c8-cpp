#include "c8-common/GetCurrentYear.hpp"
#include <gmock/gmock.h>

namespace C8::Common {
  using namespace testing;

  TEST(TestGetCurrentYear, shouldGetCurrentYear) {
    ASSERT_THAT(getCurrentYear(), Ge(2020u));
  }
} // namespace C8::Common
