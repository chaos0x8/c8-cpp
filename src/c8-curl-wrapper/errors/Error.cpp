#include "c8-curl-wrapper/errors/Error.hpp"
#include "c8-common/Format.hpp"

namespace C8::CurlWrapper::Errors {
  Error::Error(std::string_view message)
    : C8::Common::Errors::Error(Common::format("CurlWrapper::Error: %s", message.data())) {}
} // namespace C8::CurlWrapper::Errors
