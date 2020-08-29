#include "c8-crypto-wrapper/Md5.hpp"

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/hex.h>
#include <cryptopp/md5.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/pwdbased.h>

namespace C8::CryptoWrapper {
  std::string Md5::encrypt(const std::string& input) const {
    return encrypt(std::vector<char>(std::begin(input), std::end(input)));
  }

  std::string Md5::encrypt(const std::vector<char>& input) const {
    using namespace CryptoPP;

    byte digest[Weak::MD5::DIGESTSIZE];
    Weak::MD5().CalculateDigest(digest, (const byte*)input.data(), input.size());

    std::string output;
    constexpr bool LOWER_CASE = false;
    HexEncoder encoder(nullptr, LOWER_CASE);
    encoder.Attach(new StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
  }
} // namespace C8::CryptoWrapper
