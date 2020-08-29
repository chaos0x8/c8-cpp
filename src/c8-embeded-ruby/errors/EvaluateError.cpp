#include "c8-embeded-ruby/errors/EvaluateError.hpp"
#include "c8-common/Format.hpp"

namespace C8::EmbededRuby::Errors {
  EvaluateError::EvaluateError() : C8::Common::Errors::Error("EvaluateError") {}
} // namespace C8::EmbededRuby::Errors