#include "c8-option-parser/errors/InvalidOptionNameError.hpp"
#include "c8-common/Format.hpp"

namespace C8::OptionParser::Errors {
  InvalidOptionNameError::InvalidOptionNameError(std::string_view msg)
    : C8::OptionParser::Errors::Error(Common::format("InvalidOptionNameError: '%s'", msg.data())) {}
} // namespace C8::OptionParser::Errors
