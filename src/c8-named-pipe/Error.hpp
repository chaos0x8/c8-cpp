#pragma once

#include <stdexcept>

namespace C8::NamedPipe {
  struct Error : public std::runtime_error {
    Error(int errnoValue);

    static void test(bool expression) {
      if (not expression) {
        throw Error(errno);
      }
    }
  };
} // namespace C8::NamedPipe
