#pragma once

#include <string>

namespace C8::EmbededRuby {
  class GFixnum {
  public:
    explicit GFixnum(const std::string& name, long value = 0);

    GFixnum& operator=(long);

    operator long() const;

  private:
    const std::string _name;
  };
} // namespace C8::EmbededRuby
