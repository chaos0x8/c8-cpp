#pragma once

#include "c8-common/errors/Error.hpp"

namespace C8::Common::Errors {
  struct OperationAbortedError : public C8::Common::Errors::Error {
    explicit OperationAbortedError(const std::string&);
  };
} // namespace C8::Common::Errors
