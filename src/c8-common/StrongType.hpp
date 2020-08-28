#pragma once

#include <utility>

namespace C8::Common {
  template <class T, class Tag> struct StrongType {
    explicit constexpr StrongType(const T& value) : value_(value) {}

    constexpr StrongType(const StrongType<T, Tag>& other)
      : value_(other.value_) {}
    constexpr StrongType(StrongType<T, Tag>&& other)
      : value_(std::move(other.value_)) {}

    constexpr bool operator!=(const StrongType<T, Tag>& other) const {
      return value_ != other.value_;
    }
    constexpr bool operator==(const StrongType<T, Tag>& other) const {
      return value_ == other.value_;
    }

    constexpr bool operator>(const StrongType<T, Tag>& other) const {
      return value_ > other.value_;
    }
    constexpr bool operator>=(const StrongType<T, Tag>& other) const {
      return value_ >= other.value_;
    }
    constexpr bool operator<(const StrongType<T, Tag>& other) const {
      return value_ < other.value_;
    }
    constexpr bool operator<=(const StrongType<T, Tag>& other) const {
      return value_ <= other.value_;
    }

    constexpr StrongType& operator=(const StrongType<T, Tag>& other) {
      value_ = other.value_;
      return *this;
    }

    constexpr StrongType& operator=(StrongType<T, Tag>&& other) {
      value_ = std::move(other.value_);
      return *this;
    }

    constexpr const T& operator*() const {
      return value_;
    }

    constexpr T& operator*() {
      return value_;
    }

  private:
    T value_;
  };
} // namespace C8::Common
