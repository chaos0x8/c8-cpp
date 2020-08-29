#include "c8-common/errors/OperationAbortedError.hpp"
#include "c8-common/Format.hpp"

namespace C8::Common::Errors {
  OperationAbortedError::OperationAbortedError(std::string_view msg)
    : C8::Common::Errors::Error(format("OperationAbortedError: %s", msg.data())) {}
} // namespace C8::Common::Errors
