#pragma once

#include "c8-common/errors/Error.hpp"

namespace C8::OptionParser::Errors {
  struct Error : public C8::Common::Errors::Error {
    explicit Error(const std::string&);
  };
} // namespace C8::OptionParser::Errors
