#pragma once

#include <string>

namespace C8::CurlWrapper::Detail {
  inline int writeProc(char* data, size_t size, size_t nmemb, std::string* result) {
    if (data == nullptr)
      return 0;

    result->append(data, size * nmemb);

    return size * nmemb;
  }
} // namespace C8::CurlWrapper::Detail
