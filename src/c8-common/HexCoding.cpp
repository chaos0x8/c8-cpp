#include "c8-common/HexCoding.hpp"
#include <cassert>
#include <iomanip>
#include <sstream>

namespace C8::Common::HexCoding {
  std::string encrypt(const std::string& input) {
    return encrypt(std::vector<char>(std::begin(input), std::end(input)));
  }

  std::string encrypt(const std::vector<char>& input) {
    std::stringstream ss;
    ss.setf(std::ios::hex, std::ios::basefield);
    ss.fill('0');
    for (char c : input)
      ss << std::setw(2) << static_cast<uint32_t>(static_cast<uint8_t>(c));
    return ss.str();
  }

  std::vector<char> decrypt(const std::string& input) {
    return decrypt(std::vector<char>(std::begin(input), std::end(input)));
  }

  std::vector<char> decrypt(const std::vector<char>& input) {
    assert(input.size() % 2 == 0);

    uint32_t value;
    std::stringstream ss;
    std::vector<char> result(input.size() / 2);

    for (size_t i = 0; i < input.size(); i += 2) {
      ss.seekg(0);
      ss << std::dec << input[i] << input[i + 1];

      ss.seekp(0);
      ss >> std::hex >> value;
      result[i / 2] = static_cast<char>(value);
    }

    return result;
  }
} // namespace C8::Common::HexCoding
