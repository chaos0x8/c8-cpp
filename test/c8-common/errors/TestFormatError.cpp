#include "c8-common/errors/FormatError.hpp"
#include <gmock/gmock.h>

namespace C8::Common::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestFormatError : public Test {
    FormatError sut = FormatError();
  };

  TEST_F(TestFormatError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("FormatError"s));
  }
} // namespace C8::Common::Errors
