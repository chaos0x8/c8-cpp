#include "c8-crypto-wrapper/Aes.hpp"
#include <gmock/gmock.h>

namespace C8::CryptoWrapper {
  using namespace testing;

  class AesTestSuite : public Test {
  public:
    Aes sut;

    static std::vector<char> vec(const std::string& s) {
      return std::vector<char>(std::begin(s), std::end(s));
    }

    const std::string PASSWORD = "password";
    const std::string TEXT = "hello world!";
  };

  TEST_F(AesTestSuite, encryptGivesDeterministicResult) {
    ASSERT_THAT(sut.encrypt(vec(TEXT)), Not(ElementsAreArray(vec(TEXT))));
    ASSERT_THAT(sut.encrypt(TEXT), Not(ElementsAreArray(vec(TEXT))));
  }

  TEST_F(AesTestSuite, encryptGivesDifferentResultWhenPasswordIsChanged) {
    const std::vector<char> encrypted = sut.encrypt(TEXT);
    sut.setPassword(PASSWORD);

    ASSERT_THAT(encrypted, Not(ElementsAreArray(sut.encrypt(TEXT))));
  }

  TEST_F(AesTestSuite, decryptGivesDataSameAsBeforeEncryption) {
    const std::vector<char> encrypted = sut.encrypt(TEXT);

    ASSERT_THAT(sut.decrypt(encrypted), ElementsAreArray(vec(TEXT)));
  }

  TEST_F(AesTestSuite, decryptGivesDifferentDataWhenPasswordWasChanged) {
    sut.setPassword(PASSWORD);
    const std::vector<char> encrypted = sut.encrypt(TEXT);
    sut.setPassword(std::string("wrong") + PASSWORD);

    ASSERT_THAT(sut.decrypt(encrypted), Not(ElementsAreArray(vec(TEXT))));
  }
} // namespace C8::CryptoWrapper
