#pragma once

#include "errors/FormatError.hpp"

#include <array>
#include <stdio.h>
#include <string>
#include <string_view>
#include <vector>

namespace C8::Common {
  namespace Detail {
    template <class T>
    inline auto fforward(std::remove_reference_t<T>& arg) {
      if constexpr (std::is_same_v<std::decay_t<T>, std::string>) {
        return arg.c_str();
      } else if constexpr (std::is_same_v<std::decay_t<T>, std::string_view>) {
        return std::string(arg).c_str();
      } else {
        return static_cast<T&&>(arg);
      }
    }
  } // namespace Detail

  template <class... Args>
  inline std::string format(std::string_view f, Args&&... args) {
    auto size = snprintf(nullptr, 0, f.data(), Detail::fforward<Args>(args)...);

    if (size < 0) {
      throw Errors::FormatError();
    }

    std::vector<char> buffer(static_cast<size_t>(size) + 1, 0);
    size = snprintf(buffer.data(), buffer.size(), f.data(), Detail::fforward<Args>(args)...);
    if (size < 0) {
      throw Errors::FormatError();
    }
    return std::string(buffer.data(), static_cast<size_t>(size));
  }
} // namespace C8::Common
