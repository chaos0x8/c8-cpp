#pragma once

#include "c8-option-parser/errors/Error.hpp"

namespace C8::OptionParser::Errors {
  struct MissingArgumentError : public C8::OptionParser::Errors::Error {
    explicit MissingArgumentError();
  };
} // namespace C8::OptionParser::Errors
