#pragma once

#include <utility>

namespace C8::Common {
  namespace Detail {
    template <typename F>
    struct Finally {
      explicit Finally(F&& functor) : valid_(true), functor_(std::move(functor)) {}
      Finally(const Finally&) = delete;
      Finally(Finally&& other) : valid_(std::move(other.valid_)), functor_(std::move(other.functor_)) {
        other.valid_ = false;
      }

      ~Finally() {
        if (valid_) {
          try {
            functor_();
          } catch (...) {
          }
        }
      }

      Finally<F>& operator=(const Finally<F>&) = delete;
      Finally<F>& operator=(Finally<F>&& other) {
        valid_ = std::move(other->valid_);
        functor_ = std::move(other->functor_);
        other->valid_ = false;
        return *this;
      }

      void abort() {
        valid_ = false;
      }

    private:
      bool valid_;
      F functor_;
    };
  } // namespace Detail

  template <typename F>
  inline auto finally(F&& functor) {
    return Detail::Finally<F>(std::forward<F>(functor));
  }
} // namespace C8::Common
