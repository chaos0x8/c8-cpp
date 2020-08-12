#pragma once

#include "File.hpp"
#include <memory>
#include <string>

namespace NamedPipe {
  struct Pipe {
    explicit Pipe(std::string_view name);
    Pipe(const Pipe&) = delete;
    Pipe(Pipe&&);

    ~Pipe();

    Pipe& operator=(const Pipe&) = delete;
    Pipe& operator=(Pipe&&);

    File openForWrite() const;
    File openForRead() const;

  private:
    void unlink();

    std::string name_;
  };
} // namespace NamedPipe
