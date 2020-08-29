#include "c8-embeded-ruby/Evaluate.hpp"
#include "c8-embeded-ruby/detail/Utility.hpp"
#include "c8-embeded-ruby/errors/EvaluateError.hpp"
#include <memory>
#include <ruby.h>

namespace C8::EmbededRuby {
  bool execute(const char* code) {
    int status = 0;
    rb_eval_string_protect(code, &status);
    return status == 0;
  }

  bool execute(const std::string& code) {
    return execute(code.c_str());
  }

  std::string evaluate(const char* code) {
    int status = 0;
    auto v = rb_eval_string_protect(code, &status);

    if (status != 0) {
      throw Errors::EvaluateError();
    }

    return Detail::toString(v);
  }

  std::string evaluate(const std::string& code) {
    return evaluate(code.c_str());
  }
} // namespace C8::EmbededRuby
