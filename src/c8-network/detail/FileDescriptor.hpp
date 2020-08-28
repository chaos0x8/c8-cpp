#pragma once

#include "c8-common/StrongType.hpp"
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace C8::Network {
  namespace Detail {
    class FileDescriptor {
    public:
      using value_type = Common::StrongType<int, struct FileDescriptorTag>;

      FileDescriptor() = default;
      explicit FileDescriptor(value_type fd);
      FileDescriptor(const FileDescriptor& other) = delete;
      FileDescriptor(FileDescriptor&& other);
      ~FileDescriptor();

      FileDescriptor& operator=(const FileDescriptor&) = delete;
      FileDescriptor& operator=(FileDescriptor&& other);

      value_type operator*() const;
      explicit operator bool() const;

      void close();

    private:
      static constexpr value_type INVALID_VALUE = value_type(-1);

      value_type fd{INVALID_VALUE};
    };
  } // namespace Detail

  using NativeHandler = Detail::FileDescriptor::value_type;
} // namespace C8::Network
