#include "c8-embeded-ruby/detail/Utility.hpp"

namespace C8::EmbededRuby::Detail {
  std::string toString(VALUE value) {
    auto str = rb_funcall(value, rb_intern("to_s"), 0);
    return std::string(RSTRING_PTR(str), RSTRING_LEN(str));
  }
} // namespace C8::EmbededRuby::Detail
