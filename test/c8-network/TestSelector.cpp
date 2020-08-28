#include "c8-network/Pipe.hpp"
#include "c8-network/Selector.hpp"
#include <atomic>
#include <gmock/gmock.h>

namespace C8::Network {
  using namespace testing;

  class TestSelector : public Test {
  public:
    void TearDown() override {
      auto now = std::chrono::high_resolution_clock::now();
      while (
        count != expectedCount and now + std::chrono::seconds(1) >
                                     std::chrono::high_resolution_clock::now())
        std::this_thread::yield();
      ASSERT_THAT(count, Eq(expectedCount));
    }

    void incrementCount(NativeHandler nh, Pipe* selected) {
      EXPECT_THAT(nh, Eq(selected->getNativeHandler()[0]));

      std::string data = selected->read();
      count += std::stoul(data);
    }

    void incrementCountTwice(NativeHandler nh, Pipe* selected) {
      EXPECT_THAT(nh, Eq(selected->getNativeHandler()[0]));

      std::string data = selected->read();
      count += std::stoul(data) * 2;
    }

    std::array<Pipe, 4> pipes;

    Selector sut;

    uint32_t expectedCount{std::numeric_limits<uint32_t>::max()};
    std::atomic<uint32_t> count{0};
  };

  TEST_F(TestSelector, shouldCallHandlingProcedure) {
    expectedCount = 42;

    for (Pipe& pipe : pipes)
      sut.add(pipe, &TestSelector::incrementCount, this, std::placeholders::_1,
        &pipe);
    pipes[0].write("12");
    pipes[1].write("10");
    pipes[2].write("15");
    pipes[3].write("5");
  }

  TEST_F(TestSelector, shouldRemoveElementsOnlyOnce) {
    expectedCount = 17;

    for (Pipe& pipe : pipes)
      sut.add(pipe, &TestSelector::incrementCount, this, std::placeholders::_1,
        &pipe);
    sut.remove(pipes[1]);
    sut.remove(pipes[1]);
    sut.remove(pipes[2]);

    pipes[0].write("12");
    pipes[1].write("10");
    pipes[2].write("15");
    pipes[3].write("5");
  }

  TEST_F(TestSelector, addingFdTwiceShouldNotWork) {
    expectedCount = 210;

    sut.add(pipes[0], &TestSelector::incrementCount, this,
      std::placeholders::_1, &pipes[0]);
    sut.add(pipes[0], &TestSelector::incrementCountTwice, this,
      std::placeholders::_1, &pipes[0]);
    sut.add(pipes[1], &TestSelector::incrementCountTwice, this,
      std::placeholders::_1, &pipes[1]);

    pipes[0].write("10");
    pipes[1].write("100");
  }

  TEST_F(TestSelector, selectorCanBeSafetlyStoppedManually) {
    expectedCount = 0;

    sut.stop();
    sut.wait();
  }
} // namespace C8::Network
