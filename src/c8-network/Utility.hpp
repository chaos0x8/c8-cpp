#pragma once

#include <string>
#include <vector>

namespace C8::Network {
  struct IpAddress {
    int family{};
    std::string interface;
    std::string address;
  };

  std::vector<IpAddress> getIpAddresses();
  std::vector<std::string> getIpv4Addresses();
} // namespace C8::Network
