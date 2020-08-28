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
} // namespace C8::Network
