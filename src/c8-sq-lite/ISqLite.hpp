#pragma once

#include "c8-sq-lite/SelectResult.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace C8::SqLite {
  class ISqLite {
  public:
    virtual ~ISqLite() {}

    virtual void open(const std::string& fileName) = 0;
    virtual SelectResult select(const std::string& select) = 0;
    virtual void execute(const std::string& query) = 0;
    virtual int64_t getLastInsertedId() = 0;

    virtual bool transaction(std::function<void()> operation, std::ostream& = std::cerr) = 0;

    virtual void setTestMode() = 0;

    virtual operator bool() const = 0;
  };
} // namespace C8::SqLite
