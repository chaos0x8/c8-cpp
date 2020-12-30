#include "c8-common/errors/OperationAbortedError.hpp"
#include "c8-common/Format.hpp"

namespace C8::Common::Errors {
  OperationAbortedError::OperationAbortedError(const std::string& msg)
    : C8::Common::Errors::Error(format("OperationAbortedError: %s", msg)) {}
} // namespace C8::Common::Errors
