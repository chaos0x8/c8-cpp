#include "c8-option-parser/errors/UnknownOptionError.hpp"
#include "c8-common/Format.hpp"

namespace C8::OptionParser::Errors {
  UnknownOptionError::UnknownOptionError(const std::string& msg)
    : C8::OptionParser::Errors::Error(Common::format("UnknownOptionError: '%s'", msg)) {}
} // namespace C8::OptionParser::Errors
