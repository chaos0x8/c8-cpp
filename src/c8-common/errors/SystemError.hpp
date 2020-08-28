#pragma once

#include "c8-common/errors/Error.hpp"

namespace C8::Common::Errors {
  struct SystemError : public Error {
    explicit SystemError(int errnoValue);

    int errnoValue() const {
      return errnoValue_;
    }

    static void test(bool expression);

  private:
    int errnoValue_;
  };
} // namespace C8::Common::Errors
