#include "c8-curl-wrapper/errors/Error.hpp"
#include <gmock/gmock.h>

namespace C8::CurlWrapper::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestError : public Test {
    Error sut = Error("Message");
  };

  TEST_F(TestError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("CurlWrapper::Error: Message"s));
  }
} // namespace C8::CurlWrapper::Errors
