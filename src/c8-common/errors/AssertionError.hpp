#pragma once

#include "c8-common/errors/Error.hpp"
#include <string_view>

namespace C8::Common::Errors {
  struct AssertionError : public Error {
    explicit AssertionError(std::string_view message);
  };
} // namespace C8::Common::Errors
