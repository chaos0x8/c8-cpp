#include "c8-option-parser/errors/Error.hpp"
#include <gmock/gmock.h>

namespace C8::OptionParser::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestError : public Test {
    Error sut = Error("msg");
  };

  TEST_F(TestError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("msg"s));
  }
} // namespace C8::OptionParser::Errors
