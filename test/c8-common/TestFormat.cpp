#include "c8-common/Format.hpp"
#include <gmock/gmock.h>

namespace C8::Common {
  using namespace testing;
  using namespace std::string_literals;

  struct TestFormat : public Test {};

  TEST_F(TestFormat, formatsNumber) {
    ASSERT_THAT(format("%d", 42), Eq("42"));
  }

  TEST_F(TestFormat, formatsCString) {
    ASSERT_THAT(format("%s", "hello"), Eq("hello"));
  }

  TEST_F(TestFormat, formatsString) {
    ASSERT_THAT(format("%s", "hello"s), Eq("hello"));
  }

  TEST_F(TestFormat, formatsStringView) {
    std::string hello = "hello world";
    std::string_view view{hello.c_str(), 5};
    ASSERT_THAT(format("%s", view), Eq("hello"));
  }
} // namespace C8::Common
