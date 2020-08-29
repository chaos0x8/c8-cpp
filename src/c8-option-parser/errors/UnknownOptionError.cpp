#include "c8-option-parser/errors/UnknownOptionError.hpp"
#include "c8-common/Format.hpp"

namespace C8::OptionParser::Errors {
  UnknownOptionError::UnknownOptionError(std::string_view msg)
    : C8::OptionParser::Errors::Error(Common::format("UnknownOptionError: '%s'", msg.data())) {}
} // namespace C8::OptionParser::Errors
