#include "File.hpp"
#include "Error.hpp"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace C8::NamedPipe {
  struct File::Resource {
    Resource(std::string_view name, int mode)
      : fd_(::open(name.data(), mode | O_SYNC)) {}
    Resource(const Resource&) = delete;

    ~Resource() {
      if (fd_ >= 0) {
        ::close(fd_);
      }
    }

    Resource& operator=(const Resource&) = delete;

    std::string read() {
      uint32_t size = 0u;
      Error::test(::read(fd_, &size, sizeof(size)) == sizeof(size));

      std::string result(size, 0);
      Error::test(::read(fd_, result.data(), result.size()) ==
                  static_cast<ssize_t>(size));

      return result;
    }

    void write(std::string_view txt) {
      uint32_t size = txt.size();
      Error::test(::write(fd_, &size, sizeof(size)) == sizeof(size));
      Error::test(
        ::write(fd_, txt.data(), txt.size()) == static_cast<ssize_t>(size));
    }

  private:
    int fd_;
  };

  File::File(std::string_view name, int mode)
    : resource_(std::make_unique<Resource>(name, mode)) {}

  File::~File() = default;

  std::string File::read() {
    return resource_->read();
  }

  void File::write(std::string_view txt) {
    resource_->write(txt);
  }
} // namespace C8::NamedPipe
