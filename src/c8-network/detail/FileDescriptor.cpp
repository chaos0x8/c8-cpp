#include "c8-network/detail/FileDescriptor.hpp"
#include <unistd.h>
#include <utility>

namespace C8::Network::Detail {
  FileDescriptor::FileDescriptor(value_type fd) : fd(std::move(fd)) {}

  FileDescriptor::FileDescriptor(FileDescriptor&& other)
    : fd(std::move(other.fd)) {
    other.fd = INVALID_VALUE;
  }

  FileDescriptor::~FileDescriptor() {
    close();
  }

  FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) {
    this->close();
    this->fd = std::move(other.fd);
    other.fd = INVALID_VALUE;

    return *this;
  }

  FileDescriptor::value_type FileDescriptor::operator*() const {
    return fd;
  }

  FileDescriptor::operator bool() const {
    return fd != INVALID_VALUE;
  }

  void FileDescriptor::close() {
    if (operator bool())
      ::close(*fd);
    fd = INVALID_VALUE;
  }

} // namespace C8::Network::Detail
