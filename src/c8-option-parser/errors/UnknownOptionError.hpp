#pragma once

#include "c8-option-parser/errors/Error.hpp"

namespace C8::OptionParser::Errors {
  struct UnknownOptionError : public C8::OptionParser::Errors::Error {
    explicit UnknownOptionError(std::string_view);
  };
} // namespace C8::OptionParser::Errors
