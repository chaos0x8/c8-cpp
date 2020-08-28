#pragma once

#include "UdpHost.hpp"

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace C8::Network {
  struct UdpMessage {
    std::string data;
    sockaddr_storage address{};
    socklen_t addressLength{sizeof(sockaddr_storage)};

    //! \throw Common::Errors::SystemError
    UdpHost getHost();

    UdpMessage clone(const std::string& data) const;
  };
} // namespace C8::Network
