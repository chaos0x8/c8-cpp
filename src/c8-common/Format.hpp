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

    std::vector<char> buffer(size + 1, 0);
    size = snprintf(buffer.data(), buffer.size(), f.data(), std::forward<Args>(args)...);
    return std::string(buffer.data(), size);
  }
} // namespace C8::Common
