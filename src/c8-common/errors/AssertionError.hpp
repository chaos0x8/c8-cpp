#pragma once

#include "c8-common/errors/Error.hpp"

namespace C8::Common::Errors {
  struct AssertionError : public Error {
    explicit AssertionError(const std::string& message);
  };
} // namespace C8::Common::Errors
