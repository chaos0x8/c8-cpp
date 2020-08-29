#pragma once

#include <curl/curl.h>
#include <memory>
#include <string>

namespace C8::CurlWrapper::Detail {
  struct GlobalInit;

  struct Handle {
    Handle();
    Handle(const Handle&) = delete;
    Handle(Handle&& other);

    ~Handle();

    Handle& operator=(const Handle&) = delete;
    Handle& operator=(Handle&& other);

    std::string get(const std::string& url);

  private:
    std::shared_ptr<GlobalInit> global;
    CURL* handle;
  };
} // namespace C8::CurlWrapper::Detail
