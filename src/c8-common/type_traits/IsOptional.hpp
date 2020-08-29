#pragma once

#include <optional>

namespace C8::Common::TypeTraits {
  template <class T>
  struct IsOptional {
    static constexpr bool value = false;
  };

  template <class T>
  struct IsOptional<std::optional<T>> {
    static constexpr bool value = true;
  };

  template <class T>
  constexpr bool IsOptional_v = IsOptional<T>::value;
} // namespace C8::Common::TypeTraits
