#include "File.hpp"
#include "Error.hpp"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace NamedPipe {
  struct File::Resource {
    Resource(std::string_view name, int mode)
      : fd_(::open(name.data(), mode | O_SYNC)) {}
    Resource(const Resource&) = delete;

    ~Resource() {
      if (fd_ >= 0) {
        ::close(fd_);
      }
    }

    std::string read() {
      uint32_t size = 0u;
      ::read(fd_, &size, sizeof(size));

      std::string result(size, 0);
      ::read(fd_, result.data(), result.size());

      return result;
    }

    void write(std::string_view txt) {
      uint32_t size = txt.size();
      ::write(fd_, &size, sizeof(size));
      ::write(fd_, txt.data(), txt.size());
    }

    Resource& operator=(const Resource&) = delete;

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
} // namespace NamedPipe
