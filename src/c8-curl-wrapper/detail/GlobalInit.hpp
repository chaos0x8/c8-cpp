#pragma once

#include <memory>

namespace C8::CurlWrapper::Detail {
  struct GlobalInit {
    GlobalInit();
    ~GlobalInit();

    static std::shared_ptr<GlobalInit> getInstance();

  private:
    static std::weak_ptr<GlobalInit> instance;
  };
} // namespace C8::CurlWrapper::Detail
