#pragma once

#include "detail/BaseSocket.hpp"

namespace C8::Network {
  class UdpClient : public Detail::BaseSocket {
  public:
    UdpClient() noexcept = default;

    //! \throw Common::Errors::SystemError
    UdpClient(const std::string& ip, const std::string& port);

    //! \throw Common::Errors::SystemError
    void send(const std::string& data);

    //! \throw Common::Errors::SystemError
    std::string receive();

    //! \throw Common::Errors::SystemError
    using Detail::BaseSocket::shutdown;
  };
} // namespace C8::Network
