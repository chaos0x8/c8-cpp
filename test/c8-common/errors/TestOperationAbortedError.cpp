#include "c8-common/errors/OperationAbortedError.hpp"
#include <gmock/gmock.h>

namespace C8::Common::Errors {
  using namespace testing;
  using namespace std::string_literals;

  struct TestOperationAbortedError : public Test {
    OperationAbortedError sut = OperationAbortedError("msg");
  };

  TEST_F(TestOperationAbortedError, testWhat) {
    ASSERT_THAT(sut.what(), Eq("OperationAbortedError: msg"s));
  }
} // namespace C8::Common::Errors
