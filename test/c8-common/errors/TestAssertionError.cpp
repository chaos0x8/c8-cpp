#include "c8-common/errors/AssertionError.hpp"
#include <gmock/gmock.h>

namespace C8::Common::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestAssertionError : public Test {
    AssertionError sut = AssertionError("too bad!");
  };

  TEST_F(TestAssertionError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("AssertionError: too bad!"s));
  }
} // namespace C8::Common::Errors
