#include "c8-curl-wrapper/errors/Error.hpp"
#include "c8-common/Format.hpp"

namespace C8::CurlWrapper::Errors {
  Error::Error(const std::string& message)
    : C8::Common::Errors::Error(Common::format("CurlWrapper::Error: %s", message)) {}
} // namespace C8::CurlWrapper::Errors
