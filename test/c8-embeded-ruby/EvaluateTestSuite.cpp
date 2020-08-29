#include "c8-embeded-ruby/Evaluate.hpp"
#include "c8-embeded-ruby/Init.hpp"
#include "c8-embeded-ruby/errors.hpp"
#include <gmock/gmock.h>

namespace C8::EmbededRuby {
  using namespace testing;

  class EvaluateTestSuite : public Test {
  public:
    static void SetUpTestCase() {
      init();
    }
  };

  TEST_F(EvaluateTestSuite, shouldEvaluateString) {
    ASSERT_THAT(evaluate("'test'"), Eq("test"));
  }

  TEST_F(EvaluateTestSuite, shouldEvaluateMath) {
    ASSERT_THAT(evaluate("20+22"), Eq("42"));
  }

  TEST_F(EvaluateTestSuite, evaluatedInvalidCommand) {
    ASSERT_THROW(evaluate("xxx"), Errors::EvaluateError);
  }

  TEST_F(EvaluateTestSuite, executesCommand) {
    ASSERT_THAT(execute("nil"), Eq(true));
  }

  TEST_F(EvaluateTestSuite, executesInvalidCommand) {
    ASSERT_THAT(execute("xxx"), Eq(false));
  }
} // namespace C8::EmbededRuby
