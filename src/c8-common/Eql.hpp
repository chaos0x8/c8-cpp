#pragma once

#include <cmath>
#include <limits>

namespace C8::Common {
  namespace Detail {
    template <typename T, typename U>
    class Eql;

    template <typename T>
    class Eql<T, T> {
    public:
      static bool f(const T& t, const T& u) {
        return std::fabs(t - u) < eps;
      }

      static constexpr T eps = std::numeric_limits<T>::epsilon();
    };

    template <typename T>
    constexpr T Eql<T, T>::eps;
  } // namespace Detail

  template <typename T, typename U>
  inline bool eql(const T& t, const U& u) {
    return Detail::Eql<T, U>::f(t, u);
  }
} // namespace C8::Common
