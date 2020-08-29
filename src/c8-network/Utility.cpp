#include "Utility.hpp"
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <memory>
#include <netinet/in.h>
#include <sys/types.h>

namespace C8::Network {
  namespace Detail {

    class IfAddrsDeleter {
    public:
      void operator()(ifaddrs* p) {
        freeifaddrs(p);
      }
    };

    std::unique_ptr<ifaddrs, Detail::IfAddrsDeleter> getifaddrs() {
      ifaddrs* ifAddrStruct{nullptr};
      getifaddrs(&ifAddrStruct);
      return std::unique_ptr<ifaddrs, Detail::IfAddrsDeleter>(ifAddrStruct);
    }
  } // namespace Detail

  std::vector<IpAddress> getIpAddresses() {
    std::vector<IpAddress> result;
    std::unique_ptr<ifaddrs, Detail::IfAddrsDeleter> ifAddrStruct = Detail::getifaddrs();

    for (ifaddrs* ifa = ifAddrStruct.get(); ifa != nullptr; ifa = ifa->ifa_next) {
      if (!ifa->ifa_addr)
        continue;

      void* tmpAddrPtr{nullptr};
      switch (ifa->ifa_addr->sa_family) {
        case AF_INET: {
          tmpAddrPtr = &reinterpret_cast<sockaddr_in*>(ifa->ifa_addr)->sin_addr;
          char addressBuffer[INET_ADDRSTRLEN];
          inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);

          IpAddress address;
          address.family = AF_INET;
          address.interface = ifa->ifa_name;
          address.address = addressBuffer;
          result.emplace_back(std::move(address));
        } break;
        case AF_INET6: {
          tmpAddrPtr = &reinterpret_cast<sockaddr_in6*>(ifa->ifa_addr)->sin6_addr;
          char addressBuffer[INET6_ADDRSTRLEN];
          inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);

          IpAddress address;
          address.family = AF_INET6;
          address.interface = ifa->ifa_name;
          address.address = addressBuffer;
          result.emplace_back(std::move(address));
        } break;
      }
    }

    return result;
  }

  std::vector<std::string> getIpv4Addresses() {
    std::vector<std::string> ips;
    auto ipAddresses = getIpAddresses();
    for (const IpAddress& ip : ipAddresses) {
      if (ip.family == AF_INET)
        ips.emplace_back(ip.address);
    }
    return ips;
  }
} // namespace C8::Network
