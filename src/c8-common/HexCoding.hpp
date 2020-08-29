#pragma once

#include <string>
#include <vector>

namespace C8::Common::HexCoding {
  std::string encrypt(const std::string&);
  std::string encrypt(const std::vector<char>&);
  std::vector<char> decrypt(const std::string&);
  std::vector<char> decrypt(const std::vector<char>&);
} // namespace C8::Common::HexCoding
