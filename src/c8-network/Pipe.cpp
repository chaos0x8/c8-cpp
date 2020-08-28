#include "Pipe.hpp"
#include "c8-common/errors/SystemError.hpp"
#include "c8-network/generated/BufferSize.hpp"
#include <array>
#include <unistd.h>

namespace C8::Network {
  Pipe::Pipe() {
    int fds[2] = {};
    if (::pipe(fds) == -1)
      throw Common::Errors::SystemError(errno);
    readPipe = Detail::FileDescriptor{NativeHandler(fds[0])};
    writePipe = Detail::FileDescriptor{NativeHandler(fds[1])};
  }

  std::string Pipe::read() {
    std::array<char, BUFFER_SIZE> buffor;
    ssize_t nread = ::read(**readPipe, buffor.data(), buffor.size());
    if (nread == -1)
      throw Common::Errors::SystemError(errno);
    return std::string(buffor.data(), nread);
  }

  void Pipe::write(const std::string& buffor) {
    if (::write(**writePipe, buffor.data(), buffor.size()) == -1)
      throw Common::Errors::SystemError(errno);
  }

  std::array<NativeHandler, 2> Pipe::getNativeHandler() const {
    return {*readPipe, *writePipe};
  }
} // namespace C8::Network
