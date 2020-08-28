#include "Selector.hpp"
#include "c8-common/errors/SystemError.hpp"
#include <iostream>
#include <vector>

namespace C8::Network {
  Selector::Selector() {
    add(internalCommunication, &Selector::internalHandler, this,
      std::placeholders::_1);
    selectorThread = std::thread(&Selector::threadProcedure, this);
  }

  Selector::~Selector() {
    stop();
    wait();
  }

  void Selector::stop() {
    internalCommunication.write("K");
  }

  void Selector::wait() {
    if (selectorThread.joinable()) {
      selectorThread.join();
    }
  }

  void Selector::addPriv(NativeHandler fd, SelectorCallback callback) {
    std::unique_lock<std::mutex> lock(itemsMutex);
    if (items
          .insert(
            std::pair<NativeHandler, SelectorCallback>(fd, std::move(callback)))
          .second) {
      internalCommunication.write("U");
    }
  }

  void Selector::remove(NativeHandler fd) {
    std::unique_lock<std::mutex> lock(itemsMutex);
    if (items.erase(fd)) {
      internalCommunication.write("U");
    }
  }

  void Selector::threadProcedure() try {
    fd_set fdSet;

    while (keepAlive) {
      FD_ZERO(&fdSet);

      auto maxFd = NativeHandler(0);
      {
        std::unique_lock<std::mutex> lock(itemsMutex);
        for (const auto& val : items) {
          maxFd = std::max(maxFd, val.first);
          FD_SET(*val.first, &fdSet);
        }
      }

      if (::select(*maxFd + 1, &fdSet, nullptr, nullptr, nullptr) == -1) {
        throw Common::Errors::SystemError(errno);
      }

      std::vector<std::pair<NativeHandler, SelectorCallback>>
        callbacksToExecute;

      {
        std::unique_lock<std::mutex> lock(itemsMutex);
        for (const auto& val : items) {
          if (FD_ISSET(*val.first, &fdSet)) {
            callbacksToExecute.emplace_back(val);
          }
        }
      }

      for (const auto& [nh, callback] : callbacksToExecute) {
        callback(nh);
      }
    }

    if (onFinish) {
      onFinish();
    }
  } catch (Common::Errors::SystemError& e) {
    std::cerr << e.what() << std::endl;

    if (onFinish) {
      onFinish();
    }
  }

  void Selector::internalHandler(NativeHandler) {
    if (internalCommunication.read().find("K") != std::string::npos) {
      keepAlive = false;
    }
  }
} // namespace C8::Network
