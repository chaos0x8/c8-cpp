#include "c8-option-parser/errors/InvalidOptionNameError.hpp"
#include <gmock/gmock.h>

namespace C8::OptionParser::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestInvalidOptionNameError : public Test {
    InvalidOptionNameError sut = InvalidOptionNameError("arg");
  };

  TEST_F(TestInvalidOptionNameError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("InvalidOptionNameError: 'arg'"s));
  }
} // namespace C8::OptionParser::Errors
