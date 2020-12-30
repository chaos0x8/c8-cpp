#include "TcpIpClient.hpp"
#include "c8-common/RuntimeAssert.hpp"
#include "c8-network/generated/BufferSize.hpp"
#include <array>

namespace C8::Network {
  TcpIpClient::TcpIpClient(const std::string& ip, const std::string& port) {
    fd = connect(ip, port, SOCK_STREAM);
  }

  void TcpIpClient::send(const std::string& data) {
    if (::send(**fd, data.data(), data.size(), 0) == -1) {
      throw Common::Errors::SystemError(errno);
    }
  }

  void TcpIpClient::send(const void* src, size_t size) {
    if (::send(**fd, src, size, 0) == -1) {
      throw Common::Errors::SystemError(errno);
    }
  }

  std::string TcpIpClient::receive() {
    std::array<char, BUFFER_SIZE> buffor;

    int r = ::recv(**fd, buffor.data(), buffor.size(), 0);
    if (r < 0) {
      throw Common::Errors::SystemError(errno);
    }

    return std::string(buffor.data(), static_cast<size_t>(r));
  }

  std::string TcpIpClient::receive(size_t size) {
    std::array<char, BUFFER_SIZE> buffor;

    Common::runtimeAssert(size <= BUFFER_SIZE, "size exceeds buffor size");

    int r = ::recv(**fd, buffor.data(), std::min(buffor.size(), size), 0);
    if (r < 0) {
      throw Common::Errors::SystemError(errno);
    }

    return std::string(buffor.data(), static_cast<size_t>(r));
  }

  bool TcpIpClient::receive(void* dst, size_t size) {
    int r = ::recv(**fd, dst, size, 0);
    if (r == -1) {
      throw Common::Errors::SystemError(errno);
    }
    return r > 0 and static_cast<size_t>(r) == size;
  }

  TcpIpClient::TcpIpClient(Detail::FileDescriptor fd) : BaseSocket(std::move(fd)) {}
} // namespace C8::Network
