#include "c8-option-parser/errors/UnknownOptionError.hpp"
#include <gmock/gmock.h>

namespace C8::OptionParser::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestUnknownOptionError : public Test {
    UnknownOptionError sut = UnknownOptionError("arg");
  };

  TEST_F(TestUnknownOptionError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("UnknownOptionError: 'arg'"s));
  }
} // namespace C8::OptionParser::Errors
