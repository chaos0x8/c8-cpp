#pragma once

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/sha.h>

namespace C8::CryptoWrapper {
  class Aes {
  public:
    void setPassword(const std::string& password);
    void setPassword(const std::vector<char>& password);

    std::vector<char> encrypt(const std::string& input) const;
    std::vector<char> encrypt(const std::vector<char>& input) const;
    std::vector<char> decrypt(const std::string& input) const;
    std::vector<char> decrypt(const std::vector<char>& input) const;

  private:
    byte key[CryptoPP::AES::MAX_KEYLENGTH] = {};
    byte iv[CryptoPP::AES::BLOCKSIZE] = {};
  };
} // namespace C8::CryptoWrapper
