#pragma once

#include "detail/FileDescriptor.hpp"
#include <array>
#include <string>

namespace C8::Network {
  class Pipe {
  public:
    //! \throw Common::Errors::SystemError
    Pipe();

    //! \throw Common::Errors::SystemError
    std::string read();

    //! \throw Common::Errors::SystemError
    void write(const std::string& buffor);

    std::array<NativeHandler, 2> getNativeHandler() const;

  private:
    Detail::FileDescriptor readPipe;
    Detail::FileDescriptor writePipe;
  };
} // namespace C8::Network
