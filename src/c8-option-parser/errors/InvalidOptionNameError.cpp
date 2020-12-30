#include "c8-option-parser/errors/InvalidOptionNameError.hpp"
#include "c8-common/Format.hpp"

namespace C8::OptionParser::Errors {
  InvalidOptionNameError::InvalidOptionNameError(const std::string& msg)
    : C8::OptionParser::Errors::Error(Common::format("InvalidOptionNameError: '%s'", msg)) {}
} // namespace C8::OptionParser::Errors
