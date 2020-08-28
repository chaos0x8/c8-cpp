#include "Pipe.hpp"
#include "c8-common/errors/SystemError.hpp"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace C8::NamedPipe {
  using namespace std::string_literals;

  Pipe::Pipe(std::string_view name) : name_(name) {
    if (mkfifo(name_.c_str(), 0666) != 0) {
      throw Common::Errors::SystemError(errno);
    }
  }

  Pipe::Pipe(Pipe&& other) : name_(std::move(other.name_)) {
    other.name_.clear();
  }

  Pipe& Pipe::operator=(Pipe&& other) {
    unlink();
    std::swap(name_, other.name_);
    return *this;
  }

  Pipe::~Pipe() {
    unlink();
  }

  File Pipe::openForWrite() const {
    return File(name_, O_WRONLY);
  }

  File Pipe::openForRead() const {
    return File(name_, O_RDONLY);
  }

  void Pipe::unlink() {
    if (name_.size() > 0) {
      ::unlink(name_.c_str());
    }
    name_ = std::string();
  }
} // namespace C8::NamedPipe
