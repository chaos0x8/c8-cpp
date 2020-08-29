#include "c8-embeded-ruby/GString.hpp"
#include "c8-embeded-ruby/detail/Utility.hpp"
#include <ruby.h>

namespace C8::EmbededRuby {
  GString::GString(const std::string& name, const std::string& value) : _name(name) {
    VALUE v = rb_str_new_cstr(value.c_str());
    rb_gv_set(_name.c_str(), v);
  }

  GString& GString::operator=(const char* value) {
    VALUE v = rb_str_new_cstr(value);
    rb_gv_set(_name.c_str(), v);

    return *this;
  }

  GString::operator std::string() const {
    VALUE v = rb_gv_get(_name.c_str());
    return Detail::toString(v);
  }
} // namespace C8::EmbededRuby
