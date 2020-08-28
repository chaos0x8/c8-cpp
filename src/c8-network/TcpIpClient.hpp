#pragma once

#include "detail/BaseSocket.hpp"

namespace C8::Network {
  class TcpIpClient : public Detail::BaseSocket {
  public:
    TcpIpClient() noexcept = default;

    //! \throw Common::Errors::SystemError
    TcpIpClient(const std::string& ip, const std::string& port);

    //! \throw Common::Errors::SystemError
    void send(const std::string& data);

    //! \throw Common::Errors::SystemError
    void send(const void* src, size_t);

    //! \throw Common::Errors::SystemError
    std::string receive();
    std::string receive(size_t size);

    //! \throw Common::Errors::SystemError
    bool receive(void* dst, size_t);

    //! \throw Common::Errors::SystemError
    using Detail::BaseSocket::shutdown;

  private:
    TcpIpClient(Detail::FileDescriptor fd);

    friend class TcpIpServer;
  };
} // namespace C8::Network
