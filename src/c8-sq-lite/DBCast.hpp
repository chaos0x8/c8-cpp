#pragma once

#include "c8-common/type_traits.hpp"
#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>

namespace C8::SqLite::DBCast {
  namespace Detail {
    template <class T>
    struct ConvertableNumber {
      static constexpr bool value = std::is_same<unsigned, T>::value || std::is_same<unsigned long, T>::value ||
                                    std::is_same<unsigned long long, T>::value || std::is_same<int, T>::value ||
                                    std::is_same<long, T>::value || std::is_same<long long, T>::value ||
                                    std::is_same<float, T>::value || std::is_same<double, T>::value ||
                                    std::is_same<long double, T>::value;
    };

    template <typename T>
    inline T convNumber(const std::string&);

    template <>
    inline unsigned convNumber<unsigned>(const std::string& data) {
      return std::stoul(data);
    }

    template <>
    inline unsigned long convNumber<unsigned long>(const std::string& data) {
      return std::stoul(data);
    }

    template <>
    inline unsigned long long convNumber<unsigned long long>(const std::string& data) {
      return std::stoull(data);
    }

    template <>
    inline int convNumber<int>(const std::string& data) {
      return std::stoi(data);
    }

    template <>
    inline long convNumber<long>(const std::string& data) {
      return std::stol(data);
    }

    template <>
    inline long long convNumber<long long>(const std::string& data) {
      return std::stoll(data);
    }

    template <>
    inline float convNumber<float>(const std::string& data) {
      return std::stof(data);
    }

    template <>
    inline double convNumber<double>(const std::string& data) {
      return std::stod(data);
    }

    template <>
    inline long double convNumber<long double>(const std::string& data) {
      return std::stold(data);
    }
  } // namespace Detail

  template <typename T>
  inline T fromDBFormat(const std::string& data) {
    if constexpr (std::is_same_v<T, std::string>) {
      return data;
    } else if constexpr (Detail::ConvertableNumber<T>::value) {
      return Detail::convNumber<T>(data);
    } else if constexpr (Common::TypeTraits::IsOptional_v<T>) {
      if (data.empty()) {
        return std::nullopt;
      }
      return fromDBFormat<typename T::value_type>(data);
    } else {
      return boost::lexical_cast<T>(data);
    }
  }

  template <typename T>
  inline std::string toDBFormat(const T& val) {
    return boost::lexical_cast<std::string>(val);
  }

  inline std::string toDBFormat(const double& val) {
    std::ostringstream ss;
    ss << val;
    return ss.str();
  }

  inline std::string toDBFormat(const std::string& value) {
    return std::string("'") + boost::replace_all_copy(value, "'", "''") + "'";
  }

  inline std::string toDBFormat(const char* value) {
    return toDBFormat(std::string(value));
  }

  template <typename T>
  inline std::string toDBFormat(const std::optional<T>& val) {
    if (!val)
      return "null";
    return toDBFormat(*val);
  }
} // namespace C8::SqLite::DBCast
