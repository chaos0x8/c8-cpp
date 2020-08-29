#include "c8-curl-wrapper/detail/Handle.hpp"
#include "c8-curl-wrapper/detail/GlobalInit.hpp"
#include "c8-curl-wrapper/detail/WriteProc.hpp"
#include "c8-curl-wrapper/errors.hpp"
#include <curl/curl.h>

namespace C8::CurlWrapper::Detail {
  Handle::Handle() : global(GlobalInit::getInstance()), handle(curl_easy_init()) {
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1l);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeProc);
  }

  Handle::Handle(Handle&& other) : global(std::move(other.global)), handle(other.handle) {
    other.handle = nullptr;
  }

  Handle::~Handle() {
    if (handle)
      curl_easy_cleanup(handle);
  }

  Handle& Handle::operator=(Handle&& other) {
    global = std::move(other.global);
    handle = std::move(other.handle);

    other.handle = nullptr;

    return *this;
  }

  std::string Handle::get(const std::string& url) {
    std::string result;

    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &result);

    if (curl_easy_perform(handle) != CURLE_OK) {
      throw Errors::Error("perform failed!");
    }

    return result;
  }
} // namespace C8::CurlWrapper::Detail
