#pragma once

#include "errors/FormatError.hpp"

#include <array>
#include <stdio.h>
#include <string>
#include <string_view>
#include <vector>

namespace C8::Common {
  template <class... Args>
  inline std::string format(std::string_view f, Args&&... args) {
    auto size = snprintf(nullptr, 0, f.data(), std::forward<Args>(args)...);

    if (size < 0) {
      throw Errors::FormatError();
    }

    std::vector<char> buffer(static_cast<size_t>(size) + 1, 0);
    size = snprintf(buffer.data(), buffer.size(), f.data(), std::forward<Args>(args)...);
    if (size < 0) {
      throw Errors::FormatError();
    }
    return std::string(buffer.data(), static_cast<size_t>(size));
  }
} // namespace C8::Common
