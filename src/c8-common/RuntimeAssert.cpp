#include "RuntimeAssert.hpp"
#include "errors/AssertionError.hpp"

namespace C8::Common {
  void runtimeAssert(bool expression, std::string_view message) {
    if (expression == false) {
      throw Common::Errors::AssertionError(message);
    }
  }
} // namespace C8::Common
