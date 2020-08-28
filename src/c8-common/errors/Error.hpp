#pragma once

#include <stdexcept>
#include <string_view>

namespace C8::Common::Errors {
  struct Error : std::runtime_error {
    explicit Error(std::string_view msg) : std::runtime_error(msg.data()) {}
  };
} // namespace C8::Common::Errors
