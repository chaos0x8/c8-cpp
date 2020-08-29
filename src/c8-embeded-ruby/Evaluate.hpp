#pragma once

#include <string>
#include <vector>

namespace C8::EmbededRuby {
  bool execute(const char* code);
  bool execute(const std::string& code);

  std::string evaluate(const char* code);
  std::string evaluate(const std::string& code);
} // namespace C8::EmbededRuby
