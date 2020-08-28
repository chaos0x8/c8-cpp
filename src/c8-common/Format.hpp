#pragma once

#include "errors/FormatError.hpp"

#include <array>
#include <stdio.h>
#include <string>
#include <string_view>
#include <vector>

namespace C8::Common {
  template <class... Args>
  std::string format(std::string_view f, Args&&... args) {
    std::array<char, 0> dummy;

    auto size = snprintf(
      dummy.data(), dummy.size(), f.data(), std::forward<Args>(args)...);

    if (size < 0) {
      throw Errors::FormatError();
    }

    std::vector<char> buffer(size + 1, 0);
    snprintf(
      buffer.data(), buffer.size(), f.data(), std::forward<Args>(args)...);
    return std::string(buffer.data(), buffer.size() - 1);
  }
} // namespace C8::Common
