#include "c8-common/errors/Error.hpp"
#include <gmock/gmock.h>

namespace C8::Common::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestError : public Test {
    Error sut = Error("too bad!");
  };

  TEST_F(TestError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("too bad!"s));
  }
} // namespace C8::Common::Errors
