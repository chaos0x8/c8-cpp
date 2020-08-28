#include "UdpClient.hpp"
#include "generated/BufferSize.hpp"
#include <array>
#include <unistd.h>

namespace C8::Network {
  UdpClient::UdpClient(const std::string& ip, const std::string& port) {
    fd = connect(ip, port, SOCK_DGRAM);
  }

  void UdpClient::send(const std::string& data) {
    if (::write(**fd, data.data(), data.size()) == -1) {
      throw Common::Errors::SystemError(errno);
    }
  }

  std::string UdpClient::receive() {
    std::array<char, BUFFER_SIZE> buffor;

    int nread = ::read(**fd, buffor.data(), buffor.size());
    if (nread == -1) {
      throw Common::Errors::SystemError(errno);
    }
    return std::string(buffor.data(), nread);
  }
} // namespace C8::Network
