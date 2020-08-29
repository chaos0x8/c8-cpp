#include "c8-embeded-ruby/errors/EvaluateError.hpp"
#include <gmock/gmock.h>

namespace C8::EmbededRuby::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestEvaluateError : public Test {
    EvaluateError sut = EvaluateError();
  };

  TEST_F(TestEvaluateError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("EvaluateError"s));
  }
} // namespace C8::EmbededRuby::Errors