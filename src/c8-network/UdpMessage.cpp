#include "UdpMessage.hpp"
#include "c8-common/errors/SystemError.hpp"
#include <array>

namespace C8::Network {
  UdpHost UdpMessage::getHost() {
    UdpHost udpHost;

    std::array<char, NI_MAXHOST> host;
    std::array<char, NI_MAXSERV> service;

    if (::getnameinfo(reinterpret_cast<sockaddr*>(&address), addressLength,
          host.data(), host.size(), service.data(), service.size(),
          NI_NUMERICSERV) != 0) {
      throw Common::Errors::SystemError(errno);
    }

    udpHost.name = host.data();
    udpHost.service = service.data();

    return udpHost;
  }

  UdpMessage UdpMessage::clone(const std::string& data) const {
    UdpMessage cloned{};
    cloned.data = data;
    cloned.address = this->address;
    cloned.addressLength = this->addressLength;
    return cloned;
  }
} // namespace C8::Network
