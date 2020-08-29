#pragma once

#include "c8-common/errors/Error.hpp"

namespace C8::EmbededRuby::Errors {
  struct EvaluateError : public C8::Common::Errors::Error {
    explicit EvaluateError();
  };
} // namespace C8::EmbededRuby::Errors