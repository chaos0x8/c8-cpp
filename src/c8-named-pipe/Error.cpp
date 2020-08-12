#include "Error.hpp"
#include <cstring>
#include <string>

namespace NamedPipe {
  using namespace std::string_literals;

  Error::Error(int errnoValue)
    : std::runtime_error("NamedPipe::Error: "s + strerror(errnoValue)) {}
} // namespace NamedPipe
