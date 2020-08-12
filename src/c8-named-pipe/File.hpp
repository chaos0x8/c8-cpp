#pragma once

#include <memory>
#include <string>

namespace NamedPipe {
  struct File {
    File(std::string_view name, int mode);
    ~File();

    std::string read();
    void write(std::string_view);

  private:
    struct Resource;

    std::unique_ptr<Resource> resource_;
  };
} // namespace NamedPipe
