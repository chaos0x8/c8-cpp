#include "c8-curl-wrapper/Get.hpp"

#include <gmock/gmock.h>

namespace C8::CurlWrapper {
  using namespace testing;

  TEST(TestGet, getsHtmlCodeOfExampleCom) {
    EXPECT_THAT(get("http://example.com/"), ContainsRegex("Example Domain"));
  }
} // namespace C8::CurlWrapper
