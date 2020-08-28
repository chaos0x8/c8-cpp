#pragma once

#include <string_view>

namespace C8::Common {
  void runtimeAssert(bool expression, std::string_view message);
}
