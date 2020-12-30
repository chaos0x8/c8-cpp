#include "c8-option-parser/errors/Error.hpp"
#include "c8-common/Format.hpp"

namespace C8::OptionParser::Errors {
  Error::Error(const std::string& msg) : C8::Common::Errors::Error(msg) {}
} // namespace C8::OptionParser::Errors
