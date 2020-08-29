#pragma once

#include <string>

namespace C8::EmbededRuby {
  class GString {
  public:
    explicit GString(const std::string& name, const std::string& value = "");

    GString& operator=(const char*);
    GString& operator=(const std::string& v) {
      return operator=(v.c_str());
    }

    operator std::string() const;

  private:
    const std::string _name;
  };
} // namespace C8::EmbededRuby
