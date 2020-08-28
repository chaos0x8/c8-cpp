#pragma once

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace C8::Network::Detail {
  struct AddrinfoDeleter {
    void operator()(addrinfo* p) {
      freeaddrinfo(p);
    }
  };
} // namespace C8::Network::Detail
