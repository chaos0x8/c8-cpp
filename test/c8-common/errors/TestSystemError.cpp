#include "c8-common/errors/SystemError.hpp"
#include <gmock/gmock.h>

namespace C8::Common::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestSystemError : public Test {
    SystemError sut = SystemError(0);
  };

  TEST_F(TestSystemError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("SystemError: Success"s));
  }

  TEST_F(TestSystemError, doesNothingWhenTestSuccess) {
    ASSERT_NO_THROW(SystemError::test(true));
  }

  TEST_F(TestSystemError, throwsWhenTestFails) {
    ASSERT_THROW(SystemError::test(false), SystemError);
  }
} // namespace C8::Common::Errors
