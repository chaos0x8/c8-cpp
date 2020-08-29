#include "c8-option-parser/errors/MissingArgumentError.hpp"
#include "c8-common/Format.hpp"

namespace C8::OptionParser::Errors {
  MissingArgumentError::MissingArgumentError() : C8::OptionParser::Errors::Error("MissingArgumentError") {}
} // namespace C8::OptionParser::Errors
