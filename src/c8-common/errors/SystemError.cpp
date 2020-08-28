#include "SystemError.hpp"
#include "c8-common/Format.hpp"
#include <cstring>

namespace C8::Common::Errors {
  SystemError::SystemError(int errnoValue)
    : Error(format("SystemError: %s", strerror(errnoValue))),
      errnoValue_(errnoValue) {}

  void SystemError::test(bool expression) {
    if (not expression) {
      throw SystemError(errno);
    }
  }
} // namespace C8::Common::Errors
