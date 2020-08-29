#include "c8-sq-lite/DBCast.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <optional>

namespace C8::SqLite::DBCast {
  using namespace testing;
  using namespace std::literals;

  TEST(DBCastTestSuite, shouldCastToDbFormat) {
    ASSERT_THAT(toDBFormat(15), Eq("15"));
    ASSERT_THAT(toDBFormat(15.5), Eq("15.5"));
    ASSERT_THAT(toDBFormat("15"), Eq("'15'"));
    ASSERT_THAT(toDBFormat(std::optional<int>(15)), Eq("15"));
    ASSERT_THAT(toDBFormat(std::optional<std::string>("15")), Eq("'15'"));
    ASSERT_THAT(toDBFormat(std::optional<std::string>()), Eq("null"));
    ASSERT_THAT(toDBFormat("Hello'World"), Eq("'Hello''World'"));
    ASSERT_THAT(toDBFormat(std::optional<double>(12.7)), Eq("12.7"));
  }

  TEST(DBCastTestSuite, shouldCastFromDbFormat) {
    ASSERT_THAT(fromDBFormat<uint32_t>("15"), Eq(15));
    ASSERT_THAT(fromDBFormat<uint64_t>("15"), Eq(15));
    ASSERT_THAT(fromDBFormat<int>("15"), Eq(15));
    ASSERT_THAT(fromDBFormat<double>("15.5"), Eq(15.5));
    ASSERT_THAT(fromDBFormat<std::string>("15"), Eq("15"));
    ASSERT_THAT(fromDBFormat<std::optional<uint32_t>>("15"), Eq(15));
    ASSERT_THAT(fromDBFormat<std::optional<uint64_t>>("15"), Eq(15));
    ASSERT_THAT(fromDBFormat<std::optional<int>>("15"), Eq(15));
    ASSERT_THAT(fromDBFormat<std::optional<double>>("15.5"), Eq(15.5));
    ASSERT_THAT(fromDBFormat<std::optional<std::string>>("15"), Eq("15"));
    ASSERT_THAT(fromDBFormat<std::optional<uint64_t>>(""), Eq(std::nullopt));
    ASSERT_THAT(fromDBFormat<std::optional<int>>(""), Eq(std::nullopt));
    ASSERT_THAT(fromDBFormat<std::optional<double>>(""), Eq(std::nullopt));
    ASSERT_THAT(fromDBFormat<std::optional<std::string>>(""), Eq(std::nullopt));
  }

  TEST(DBCastTestSuite, shouldCastFromDbFormat_String) {
    ASSERT_THAT(fromDBFormat<uint32_t>("15"s), Eq(15));
    ASSERT_THAT(fromDBFormat<uint64_t>("15"s), Eq(15));
    ASSERT_THAT(fromDBFormat<int>("15"s), Eq(15));
    ASSERT_THAT(fromDBFormat<double>("15.5"s), Eq(15.5));
    ASSERT_THAT(fromDBFormat<std::string>("15"s), Eq("15"));
  }

  TEST(DBCastTestSuite, integralCastFromDbFormat) {
    ASSERT_TRUE(fromDBFormat<bool>("1"));
    ASSERT_FALSE(fromDBFormat<bool>("0"));
    ASSERT_EQ('s', fromDBFormat<char>("s"));
    ASSERT_EQ(-42, fromDBFormat<int>("-42"));
    ASSERT_EQ(-42, fromDBFormat<long>("-42"));
    ASSERT_EQ(-42, fromDBFormat<long long>("-42"));
    ASSERT_EQ(42, fromDBFormat<unsigned int>("42"));
    ASSERT_EQ(42, fromDBFormat<unsigned long>("42"));
    ASSERT_EQ(42, fromDBFormat<unsigned long long>("42"));
    ASSERT_FLOAT_EQ(42.2f, fromDBFormat<float>("42.2"));
    ASSERT_DOUBLE_EQ(42.2, fromDBFormat<double>("42.2"));
    ASSERT_DOUBLE_EQ(-42.2, fromDBFormat<long double>("-42.2"));
  }
} // namespace C8::SqLite::DBCast
