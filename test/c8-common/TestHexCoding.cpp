#include "c8-common/HexCoding.hpp"
#include <gmock/gmock.h>

namespace C8::Common::HexCoding {
  using namespace testing;

  class TestHexCoding : public Test {
  public:
    using V = std::vector<char>;

    static std::string binaryString() {
      const std::vector<char> vec = binaryData();
      return std::string(vec.data(), vec.size());
    }
    static std::vector<char> binaryData();

    const std::string TEXT = "a cat";
  };

  MATCHER_P(EqToString, text, "text is equal") {
    return std::lexicographical_compare(std::begin(arg), std::end(arg), std::begin(text), std::end(text)) == false &&
           std::lexicographical_compare(std::begin(text), std::end(text), std::begin(arg), std::end(arg)) == false;
  }

  TEST_F(TestHexCoding, encodeCharacters) {
    ASSERT_THAT(encrypt(V{'0', 28, 30}), Eq("301c1e"));
  }

  TEST_F(TestHexCoding, encodeCharactersWithPadding) {
    ASSERT_THAT(encrypt(V{7, 15, 12}), Eq("070f0c"));
  }

  TEST_F(TestHexCoding, decodesCharacters) {
    ASSERT_THAT(decrypt("305f6e"), EqToString(std::string("0_n")));
  }

  TEST_F(TestHexCoding, decodesEncodedData) {
    const std::string encoded = encrypt(TEXT);

    ASSERT_THAT(decrypt(encoded), EqToString(TEXT));
  }

  std::vector<char> TestHexCoding::binaryData() {
    std::vector<char> binary(256);
    for (size_t i = 0; i < binary.size(); ++i)
      binary[i] = i;
    return binary;
  }

  TEST_F(TestHexCoding, decodesEncodedBinaryData) {
    const std::string encoded = encrypt(binaryString());

    ASSERT_THAT(decrypt(encoded), EqToString(binaryData()));
  }
} // namespace C8::Common::HexCoding
