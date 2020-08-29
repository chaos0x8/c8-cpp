#include "c8-curl-wrapper/Get.hpp"
#include "c8-curl-wrapper/detail/Handle.hpp"

namespace C8::CurlWrapper {
  std::string get(const std::string& url) {
    return Detail::Handle().get(url);
  }
} // namespace C8::CurlWrapper
