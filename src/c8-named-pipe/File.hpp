#pragma once

#include <memory>
#include <string>

namespace C8::NamedPipe {
  struct File {
    File(std::string_view name, int mode);
    ~File();

    std::string read();
    void write(std::string_view);

  private:
    struct Resource;

    std::unique_ptr<Resource> resource_;
  };
} // namespace C8::NamedPipe
