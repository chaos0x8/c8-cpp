#pragma once

#include "c8-common/errors/SystemError.hpp"
#include "c8-network/detail/AddrinfoDeleter.hpp"
#include "c8-network/detail/FileDescriptor.hpp"
#include <memory>
#include <string>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace C8::Network::Detail {
  class BaseSocket {
    struct FdWithAddrinfo {
      FileDescriptor fd;
      std::unique_ptr<addrinfo, AddrinfoDeleter> address;
    };

  public:
    NativeHandler getNativeHandler() const {
      return *fd;
    }

    bool operator==(NativeHandler nh) const {
      return getNativeHandler() == nh;
    }

    bool operator!=(NativeHandler nh) const {
      return getNativeHandler() != nh;
    }

  protected:
    BaseSocket() noexcept = default;
    BaseSocket(FileDescriptor);

    //! \throw Common::Errors::SystemError
    static FileDescriptor connect(
      const std::string& ip, const std::string port, __socket_type socketType);

    //! \throw Common::Errors::SystemError
    static FileDescriptor bind(
      const std::string& ip, const std::string port, __socket_type socketType);

    //! \throw Common::Errors::SystemError
    static FileDescriptor listen(const std::string& ip, const std::string port);

    //! \throw Common::Errors::SystemError
    void shutdown();

    FileDescriptor fd{};

  private:
    //! \throw Common::Errors::SystemError
    static FdWithAddrinfo socket(
      const std::string& ip, const std::string port, __socket_type socketType);
  };
} // namespace C8::Network::Detail
