#include "c8-option-parser/errors/MissingArgumentError.hpp"
#include <gmock/gmock.h>

namespace C8::OptionParser::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestMissingArgumentError : public Test {
    MissingArgumentError sut = MissingArgumentError();
  };

  TEST_F(TestMissingArgumentError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("MissingArgumentError"s));
  }
} // namespace C8::OptionParser::Errors
