#pragma once

#include <string>
#include <vector>

namespace C8::CryptoWrapper {
  class Md5 {
  public:
    std::string encrypt(const std::string&) const;
    std::string encrypt(const std::vector<char>&) const;
  };
} // namespace C8::CryptoWrapper
