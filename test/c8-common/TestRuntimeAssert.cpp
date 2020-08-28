#include "c8-common/RuntimeAssert.hpp"
#include "c8-common/errors/AssertionError.hpp"
#include <gmock/gmock.h>

namespace C8::Common {
  using namespace testing;

  class TestRuntimeAssert : public Test {
  public:
    const std::string TEXT = "assert message";
  };

  TEST_F(TestRuntimeAssert, doesNothingWhenExpressionIsTrue) {
    ASSERT_NO_THROW(runtimeAssert(true, TEXT));
  }

  TEST_F(TestRuntimeAssert, throwsWhenExpressionIsFalse) {
    try {
      runtimeAssert(false, TEXT);
      FAIL() << "Exception was not thrown!";
    } catch (Errors::AssertionError& e) {
      using S = std::string;
      ASSERT_THAT(S{e.what()}, Eq(S{Errors::AssertionError(TEXT).what()}));
    }
  }
} // namespace C8::Common
