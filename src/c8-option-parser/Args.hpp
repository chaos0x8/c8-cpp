#pragma once

#include "Error.hpp"
#include <deque>
#include <string>
#include <string_view>

namespace C8::OptionParser {
  struct Args {
    using size_type = size_t;
    using value_type = std::string;
    using iterator = std::deque<value_type>::const_iterator;
    using const_iterator = std::deque<value_type>::const_iterator;

    explicit Args(std::deque<value_type> args) : args_(std::move(args)) {}
    Args(const Args&) = delete;
    Args(Args&&) = default;

    Args& operator=(const Args&) = delete;
    Args& operator=(Args&&) = default;

    size_t size() const {
      return args_.size();
    }

    iterator begin() const {
      return std::cbegin(args_);
    }

    iterator end() const {
      return std::cend(args_);
    }

    std::string_view operator[](size_t index) const {
      return args_[index];
    }

    value_type take() {
      if (args_.size() == 0)
        throw MissingArgumentError();

      value_type result = args_.front();
      args_.pop_front();
      return result;
    }

  private:
    std::deque<value_type> args_;
  };
} // namespace C8::OptionParser
