#pragma once

#include "Pipe.hpp"
#include <atomic>
#include <functional>
#include <map>
#include <mutex>
#include <thread>

namespace C8::Network {
  using SelectorCallback = std::function<void(NativeHandler)>;

  class Selector {
  public:
    Selector();
    Selector(const Selector&) = delete;
    ~Selector();

    Selector& operator=(const Selector&) = delete;

    void stop();
    void wait();

    template <class T, class F, class... Args>
    void add(const T& t, F&& f, Args&&... args) {
      const auto fd = getNativeHandler(t);

      if constexpr (sizeof...(Args) > 0) {
        addPriv(fd, std::bind(std::forward<F>(f), std::forward<Args>(args)...));
      } else {
        addPriv(fd, std::forward<F>(f));
      }
    }

    template <class T> void remove(const T& t) {
      remove(getNativeHandler(t));
    }

    void on_finish(std::function<void()> f) {
      onFinish = std::move(f);
    }

  private:
    template <class T> static NativeHandler getNativeHandler(const T& t);

    void clear();

    void addPriv(NativeHandler fd, SelectorCallback);
    void remove(NativeHandler fd);
    void threadProcedure();
    void internalHandler(NativeHandler);

    std::atomic<bool> keepAlive{true};
    std::mutex itemsMutex;
    Pipe internalCommunication;
    std::thread selectorThread;
    std::map<NativeHandler, SelectorCallback> items;
    std::function<void()> onFinish;
  };

  template <class T>
  inline NativeHandler Selector::getNativeHandler(const T& t) {
    return t.getNativeHandler();
  }

  template <>
  inline NativeHandler Selector::getNativeHandler<Pipe>(const Pipe& t) {
    return t.getNativeHandler()[0];
  }
} // namespace C8::Network
