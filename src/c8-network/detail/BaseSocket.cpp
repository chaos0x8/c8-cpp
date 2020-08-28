#include "c8-network/detail/BaseSocket.hpp"

namespace C8::Network::Detail {
  BaseSocket::BaseSocket(FileDescriptor fd) : fd(std::move(fd)) {}

  FileDescriptor BaseSocket::connect(
    const std::string& ip, const std::string port, __socket_type socketType) {
    FdWithAddrinfo r = socket(ip, port, socketType);

    if (::connect(**r.fd, r.address->ai_addr, r.address->ai_addrlen) == -1) {
      throw Common::Errors::SystemError(errno);
    }

    return std::move(r.fd);
  }

  FileDescriptor BaseSocket::bind(
    const std::string& ip, const std::string port, __socket_type socketType) {
    FdWithAddrinfo r = socket(ip, port, socketType);

    int yes = 1;
    if (::setsockopt(**r.fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) ==
        -1) {
      throw Common::Errors::SystemError(errno);
    }

    if (::bind(**r.fd, r.address->ai_addr, r.address->ai_addrlen) == -1) {
      throw Common::Errors::SystemError(errno);
    }

    return std::move(r.fd);
  }

  FileDescriptor BaseSocket::listen(
    const std::string& ip, const std::string port) {
    FileDescriptor fd = bind(ip, port, SOCK_STREAM);

    if (::listen(**fd, SOMAXCONN) == -1) {
      throw Common::Errors::SystemError(errno);
    }

    return fd;
  }

  void BaseSocket::shutdown() {
    if (::shutdown(**fd, SHUT_RDWR) == -1) {
      throw Common::Errors::SystemError(errno);
    }
  }

  BaseSocket::FdWithAddrinfo BaseSocket::socket(
    const std::string& ip, const std::string port, __socket_type socketType) {
    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;    //! Allows IPv4 or IPv6
    hints.ai_socktype = socketType; //! Basicly TcpIp or Udp
    hints.ai_flags = AI_PASSIVE;    //! Wildcard IP address
    hints.ai_protocol = 0;          //! Any

    addrinfo* address{nullptr};
    if (::getaddrinfo(ip.c_str(), port.c_str(), &hints, &address) != 0) {
      throw Common::Errors::SystemError(errno);
    }

    std::unique_ptr<addrinfo, Detail::AddrinfoDeleter> _address{address};

    FileDescriptor fd{NativeHandler(::socket(
      address->ai_family, address->ai_socktype, address->ai_protocol))};
    if (!fd) {
      throw Common::Errors::SystemError(errno);
    }

    FdWithAddrinfo result;
    result.fd = std::move(fd);
    result.address = std::move(_address);
    return result;
  }
} // namespace C8::Network::Detail
