#include "c8-embeded-ruby/GFixnum.hpp"
#include <ruby.h>

namespace C8::EmbededRuby {
  GFixnum::GFixnum(const std::string& name, long value) : _name(name) {
    VALUE v = LONG2FIX(value);
    rb_gv_set(_name.c_str(), v);
  }

  GFixnum& GFixnum::operator=(long value) {
    VALUE v = LONG2FIX(value);
    rb_gv_set(_name.c_str(), v);

    return *this;
  }

  GFixnum::operator long() const {
    VALUE v = rb_gv_get(_name.c_str());
    return FIX2LONG(v);
  }
} // namespace C8::EmbededRuby
