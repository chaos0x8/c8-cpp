#pragma once

#include <chrono>
#include <functional>
#include <ostream>

namespace C8::Common {
  template <class F, class... Args>
  void measureTime(std::string_view title, std::ostream& out, F&& operation, Args&&... args) {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();
    operation(std::forward<Args>(args)...);
    auto end = high_resolution_clock::now();

    out << title << " took " << duration_cast<milliseconds>(end - start).count() << " ms\n";
  }
} // namespace C8::Common
