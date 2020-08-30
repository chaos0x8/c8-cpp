#include "c8-common/Finally.hpp"
#include <gmock/gmock.h>
#include <stdexcept>

namespace C8::Common {
  using namespace testing;

  struct TestFinally : public Test {
    int value = 0;
  };

  TEST_F(TestFinally, executesGivenFunctionInDestructor) {
    {
      const auto sut = finally([this] { ++value; });

      EXPECT_THAT(value, Eq(0));
    }

    EXPECT_THAT(value, Eq(1));
  }

  TEST_F(TestFinally, preventsExecutionWhenAbortIsCalled) {
    {
      auto sut = finally([this] { ++value; });

      sut.abort();
    }

    EXPECT_THAT(value, Eq(0));
  }

  TEST_F(TestFinally, ignoresAllExceptions) {
    {
      const auto sut = finally([this] {
        throw std::logic_error("it could be anything");
        ++value;
      });
    }

    EXPECT_THAT(value, Eq(0));
  }
} // namespace C8::Common
