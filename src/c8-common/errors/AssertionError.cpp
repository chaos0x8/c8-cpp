#include "AssertionError.hpp"
#include "c8-common/Format.hpp"

namespace C8::Common::Errors {
  AssertionError::AssertionError(const std::string& message) : Error(format("AssertionError: %s", message)) {}
} // namespace C8::Common::Errors
