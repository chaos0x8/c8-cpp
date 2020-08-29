#pragma once

#include "c8-common/errors/Error.hpp"

namespace C8::Common::Errors {
  struct OperationAbortedError : public C8::Common::Errors::Error {
    explicit OperationAbortedError(std::string_view);
  };
} // namespace C8::Common::Errors
