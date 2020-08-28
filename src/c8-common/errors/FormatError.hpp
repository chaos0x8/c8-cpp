#pragma once

#include "c8-common/errors/Error.hpp"

namespace C8::Common::Errors {
  struct FormatError : public Error {
    explicit FormatError() : Error("FormatError") {}
  };
} // namespace C8::Common::Errors
