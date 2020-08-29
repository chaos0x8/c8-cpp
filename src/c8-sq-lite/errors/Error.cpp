#include "c8-sq-lite/errors/Error.hpp"
#include "c8-common/Format.hpp"

namespace C8::SqLite::Errors {
  Error::Error(std::string_view message)
    : C8::Common::Errors::Error(Common::format("SqLite::Error: %s", message.data())) {}
} // namespace C8::SqLite::Errors
