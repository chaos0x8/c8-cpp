#pragma once

#include "TcpIpClient.hpp"
#include "detail/BaseSocket.hpp"

namespace C8::Network {
  class TcpIpServer : public Detail::BaseSocket {
  public:
    TcpIpServer() noexcept = default;

    //! \throw Common::Errors::SystemError
    TcpIpServer(const std::string& ip, const std::string& port);

    //! \throw Common::Errors::SystemError
    TcpIpClient accept();

    //! \throw Common::Errors::SystemError
    //! \brief accepting connection after shutdown throw exception
    using Detail::BaseSocket::shutdown;
  };
} // namespace C8::Network
