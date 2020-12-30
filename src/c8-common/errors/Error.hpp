#pragma once

#include <stdexcept>
#include <string>

namespace C8::Common::Errors {
  struct Error : std::runtime_error {
    explicit Error(const std::string& msg) : std::runtime_error(msg) {}
  };
} // namespace C8::Common::Errors
