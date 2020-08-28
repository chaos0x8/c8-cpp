#include "TcpIpServer.hpp"

namespace C8::Network {
  TcpIpServer::TcpIpServer(const std::string& ip, const std::string& port) {
    fd = listen(ip, port);
  }

  TcpIpClient TcpIpServer::accept() {
    int acceptResult = ::accept(**fd, nullptr, nullptr);
    if (acceptResult < 0) {
      throw Common::Errors::SystemError(errno);
    }
    return TcpIpClient{Detail::FileDescriptor{NativeHandler(acceptResult)}};
  }
} // namespace C8::Network
