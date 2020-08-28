#pragma once

#include "UdpMessage.hpp"
#include "detail/BaseSocket.hpp"

namespace C8::Network {
  class UdpServer : public Detail::BaseSocket {
  public:
    //! \throw Common::Errors::SystemError
    UdpServer(const std::string& ip, const std::string& port);

    //! \throw Common::Errors::SystemError
    UdpMessage receive();

    //! \throw Common::Errors::SystemError
    void send(UdpMessage msg);
  };
} // namespace C8::Network
