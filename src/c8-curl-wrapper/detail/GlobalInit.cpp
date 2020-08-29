#include "c8-curl-wrapper/detail/GlobalInit.hpp"
#include <curl/curl.h>

namespace C8::CurlWrapper::Detail {
  GlobalInit::GlobalInit() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
  }

  GlobalInit::~GlobalInit() {
    curl_global_cleanup();
  }

  std::shared_ptr<GlobalInit> GlobalInit::getInstance() {
    if (auto result = instance.lock())
      return result;

    auto result = std::make_shared<GlobalInit>();
    instance = result;
    return result;
  }

  std::weak_ptr<GlobalInit> GlobalInit::instance;
} // namespace C8::CurlWrapper::Detail
