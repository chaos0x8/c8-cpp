#include "AssertionError.hpp"
#include "c8-common/Format.hpp"

namespace C8::Common::Errors {
  AssertionError::AssertionError(std::string_view message)
    : Error(format("AssertionError: %s", message.data())) {}
} // namespace C8::Common::Errors
