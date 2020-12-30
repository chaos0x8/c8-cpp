#include "UdpServer.hpp"
#include "generated/BufferSize.hpp"
#include <array>

namespace C8::Network {
  UdpServer::UdpServer(const std::string& ip, const std::string& port) {
    fd = bind(ip, port, SOCK_DGRAM);
  }

  UdpMessage UdpServer::receive() {
    std::array<char, BUFFER_SIZE> buffor;
    UdpMessage msg{};

    ssize_t nread =
      ::recvfrom(**fd, buffor.data(), buffor.size(), 0, reinterpret_cast<sockaddr*>(&msg.address), &msg.addressLength);
    if (nread < 0) {
      throw Common::Errors::SystemError(errno);
    }

    msg.data = std::string(buffor.data(), static_cast<size_t>(nread));

    return msg;
  }

  void UdpServer::send(UdpMessage msg) {
    if (::sendto(**fd, msg.data.data(), msg.data.size(), 0, reinterpret_cast<sockaddr*>(&msg.address),
          msg.addressLength) != static_cast<ssize_t>(msg.data.size())) {
      throw Common::Errors::SystemError(errno);
    }
  }
} // namespace C8::Network
