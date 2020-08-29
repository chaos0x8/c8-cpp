#include "c8-sq-lite/errors/Error.hpp"
#include <gmock/gmock.h>

namespace C8::SqLite::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestError : public Test {
    Error sut = Error("Message");
  };

  TEST_F(TestError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("SqLite::Error: Message"s));
  }
} // namespace C8::SqLite::Errors
