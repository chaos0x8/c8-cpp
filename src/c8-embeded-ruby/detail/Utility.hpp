#pragma once

#include <ruby.h>
#include <string>

namespace C8::EmbededRuby::Detail {
  std::string toString(VALUE value);
}
