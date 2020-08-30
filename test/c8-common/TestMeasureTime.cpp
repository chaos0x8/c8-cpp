#include "c8-common/Format.hpp"
#include "c8-common/MeasureTime.hpp"
#include <chrono>
#include <gmock/gmock.h>
#include <sstream>
#include <thread>

namespace C8::Common {
  using namespace testing;
  using namespace std::chrono_literals;

  class TestMeasurements : public Test {
  public:
    static constexpr std::string_view TITLE = "title";

    std::stringstream output;
  };

  void testFunction(std::chrono::milliseconds time) {
    std::this_thread::sleep_for(time);
  }

  TEST_F(TestMeasurements, measuresFastLambdaExecutionTime) {
    measureTime(TITLE, output, [] {});

    ASSERT_THAT(output.str(), MatchesRegex(format("%s took [0-9] ms\n", TITLE.data())));
  }

  TEST_F(TestMeasurements, measuresSlowLambdaExecutionTime) {
    measureTime(TITLE, output, [] { std::this_thread::sleep_for(10ms); });

    ASSERT_THAT(output.str(), MatchesRegex(format("%s took [0-9]{2} ms\n", TITLE.data())));
  }

  TEST_F(TestMeasurements, measuresFastFunctionExecutionTime) {
    measureTime(TITLE, output, &testFunction, 0ms);

    ASSERT_THAT(output.str(), MatchesRegex(format("%s took [0-9] ms\n", TITLE.data())));
  }

  TEST_F(TestMeasurements, measuresSlowFunctionExecutionTime) {
    measureTime(TITLE, output, &testFunction, 10ms);

    ASSERT_THAT(output.str(), ContainsRegex(format("%s took [0-9]{2} ms\n", TITLE.data())));
  }
} // namespace C8::Common
