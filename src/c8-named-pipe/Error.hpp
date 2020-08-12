#pragma once

#include <stdexcept>

namespace NamedPipe {
  struct Error : public std::runtime_error {
    Error(int errnoValue);
  };
} // namespace NamedPipe
