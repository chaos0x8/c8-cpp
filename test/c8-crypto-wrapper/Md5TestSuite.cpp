#include "c8-common/HexCoding.hpp"
#include "c8-crypto-wrapper/Md5.hpp"
#include <gmock/gmock.h>

namespace C8::CryptoWrapper {
  using namespace testing;

  class Md5TestSuite : public Test {
  public:
    Md5 sut;

    const std::string TEXT = "Hello world!";
  };

  MATCHER(Hex, "should be hex") {
    return arg.size() > 0 and arg.find_first_not_of("0123456789abcdef") == std::string::npos;
  }

  TEST_F(Md5TestSuite, returnsMd5String) {
    ASSERT_THAT(sut.encrypt(TEXT), Hex());
  }

  TEST_F(Md5TestSuite, resultIsDeterministic) {
    ASSERT_THAT(sut.encrypt(TEXT), Eq(sut.encrypt(TEXT)));
  }

  TEST_F(Md5TestSuite, resultIsDifferentThanInput) {
    ASSERT_THAT(sut.encrypt(TEXT), Not(Eq(TEXT)));
  }

  TEST_F(Md5TestSuite, resultIsEncrypted) {
    using Common::HexCoding::encrypt;

    ASSERT_THAT(sut.encrypt(TEXT), Not(Eq(encrypt(TEXT))));
  }
} // namespace C8::CryptoWrapper
