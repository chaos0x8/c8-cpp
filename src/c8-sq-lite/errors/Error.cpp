#include "c8-sq-lite/errors/Error.hpp"
#include "c8-common/Format.hpp"

namespace C8::SqLite::Errors {
  Error::Error(const std::string& message) : C8::Common::Errors::Error(Common::format("SqLite::Error: %s", message)) {}
} // namespace C8::SqLite::Errors
