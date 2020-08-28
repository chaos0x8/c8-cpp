#include "c8-option-parser/Error.hpp"
#include "c8-option-parser/Parser.hpp"
#include <gmock/gmock.h>

struct Foo {
  static Foo fromString(std::string_view str) {
    auto ret = Foo{};
    ret.a = std::stoll(std::string(str));
    ret.b = str.size();
    return ret;
  }

  int a;
  int b;
};

namespace C8::OptionParser {
  using namespace testing;

  struct ParserTestSuite : public Test {
    Parser sut;
  };

  TEST_F(ParserTestSuite, accessBooleanParameterNotPresent) {
    auto help = sut.on<bool>("--help", "displays help");

    sut.parse({});

    ASSERT_THAT(static_cast<bool>(help), Eq(false));
    EXPECT_THAT(help, AllOf(Ne(false), Ne(true)));
    EXPECT_THAT(sut.args(), SizeIs(0u));
  }

  TEST_F(ParserTestSuite, accessBooleanParameterPresent) {
    auto help = sut.on<bool>("--help", "displays help");

    sut.parse({"--help"});

    ASSERT_THAT(static_cast<bool>(help), Eq(true));
    EXPECT_THAT(*help, Eq(true));
    EXPECT_THAT(help, Eq(true));
    EXPECT_THAT(sut.args(), SizeIs(0u));
  }

  TEST_F(ParserTestSuite, accessStringParameterNotPresent) {
    auto name = sut.on<std::string>("--name", "sets name");

    sut.parse({});

    ASSERT_THAT(static_cast<bool>(name), Eq(false));
    EXPECT_THAT(sut.args(), SizeIs(0u));
  }

  TEST_F(ParserTestSuite, accessStringParameterPresent) {
    auto name = sut.on<std::string>("--name", "sets name");

    sut.parse({"--name", "Lara"});

    ASSERT_THAT(static_cast<bool>(name), Eq(true));
    EXPECT_THAT(*name, Eq("Lara"));
    EXPECT_THAT(name, Eq("Lara"));
    EXPECT_THAT(sut.args(), SizeIs(0u));
  }

  TEST_F(ParserTestSuite, accessUnsignedParameterPresent) {
    auto age = sut.on<uint8_t>("--age", "sets age");
    auto height = sut.on<uint32_t>("--height", "sets height");

    sut.parse({"--age", "42", "--height", "128"});

    EXPECT_THAT(age, Eq(42u));
    EXPECT_THAT(height, Eq(128u));
    EXPECT_THAT(sut.args(), SizeIs(0u));
  }

  TEST_F(ParserTestSuite, accessSignedParameterPresent) {
    auto temp = sut.on<int8_t>("--temperature", "sets temperature");
    auto money = sut.on<int32_t>("--money", "sets money");

    sut.parse({"--temperature", "-10", "--money", "-42"});

    EXPECT_THAT(temp, Eq(-10));
    EXPECT_THAT(money, Eq(-42));
    EXPECT_THAT(sut.args(), SizeIs(0u));
  }

  TEST_F(ParserTestSuite, accessFloatingPointParameterPresent) {
    auto temp = sut.on<float>("--temperature", "sets temperature");
    auto money = sut.on<double>("--money", "sets money");

    sut.parse({"--temperature", "-10.7", "--money", "42.8"});

    EXPECT_THAT(temp, Eq(-10.7f));
    EXPECT_THAT(money, Eq(42.8));
    EXPECT_THAT(sut.args(), SizeIs(0u));
  }

  TEST_F(ParserTestSuite, accessCustomClassParameterPresent) {
    auto foo = sut.on<Foo>("--foo", "sets foo");

    sut.parse({"--foo", "142"});

    EXPECT_THAT(foo->a, Eq(142));
    EXPECT_THAT(foo->b, Eq(3));
    EXPECT_THAT(sut.args(), SizeIs(0u));
  }

  TEST_F(ParserTestSuite, accessLambdaParameterPresentWithoutArg) {
    bool help = false;

    sut.on<0>("--help", "displays help", [&help] { help = true; });
    sut.parse({"--help"});

    ASSERT_THAT(help, Eq(true));
  }

  TEST_F(ParserTestSuite, accessLambdaParameterNotPresentWithoutArg) {
    bool help = false;

    sut.on<0>("--help", "displays help", [&help] { help = true; });
    sut.parse({});

    ASSERT_THAT(help, Eq(false));
  }

  TEST_F(ParserTestSuite, accessLambdaParameterPresentWithArg) {
    std::string help;

    sut.on<1>(
      "--help", "displays help", [&help](std::string_view arg) { help = arg; });
    sut.parse({"--help", "me"});

    ASSERT_THAT(help, Eq("me"));
  }

  TEST_F(ParserTestSuite, accessLambdaParameterNotPresentWithArg) {
    std::string help;

    sut.on<1>(
      "--help", "displays help", [&help](std::string_view arg) { help = arg; });
    sut.parse({});

    ASSERT_THAT(help, Eq(""));
  }

  TEST_F(ParserTestSuite, throwWhenRegisteringOptionWithInvalidName) {
    ASSERT_THROW(sut.on<bool>("help", "displays help"), InvalidOptionNameError);
  }

  TEST_F(ParserTestSuite, throwWhenUnknownArgumentPassed) {
    sut.on<bool>("--help", "displays help");
    ASSERT_THROW(sut.parse({"--something"}), UnknownOptionError);
  }

  TEST_F(ParserTestSuite, acceptAnyStringAfterDelimeter) {
    sut.on<bool>("--help", "displays help");
    sut.parse({"--", "--something"});

    ASSERT_THAT(sut.args(), ElementsAre("--something"));
  }

  struct ParserArgsAccessTestSuite : public ParserTestSuite {
    void SetUp() override {
      std::array<const char*, 5> args = {"app", "a0", "a1", "a2", "a3"};
      sut.parse(4, args.data());
    }
  };

  TEST_F(ParserArgsAccessTestSuite, accessElements) {
    EXPECT_THAT(sut.args(), ElementsAre("a0", "a1", "a2"));
  }

  TEST_F(ParserArgsAccessTestSuite, randomAccessElements) {
    auto args = sut.args();

    ASSERT_THAT(args, SizeIs(3));
    EXPECT_THAT(args[0], Eq("a0"));
    EXPECT_THAT(args[1], Eq("a1"));
    EXPECT_THAT(args[2], Eq("a2"));
  }

  TEST_F(ParserArgsAccessTestSuite, shouldTakeArguments) {
    auto args = sut.args();

    EXPECT_THAT(args.take(), Eq("a0"));
    EXPECT_THAT(args.take(), Eq("a1"));
    EXPECT_THAT(args.take(), Eq("a2"));
  }

  TEST_F(ParserArgsAccessTestSuite, raiseWhenTookTooMuchArguments) {
    auto args = sut.args();

    while (args.size() > 0) {
      ASSERT_NO_THROW(args.take());
    }

    ASSERT_THROW(args.take(), MissingArgumentError);
  }

  struct ParserHelpTestSuite : public ParserTestSuite {
    std::array<const char*, 1> args = {"appName"};

    Option<std::string> name = sut.on<std::string>("--name", "sets name");
    Option<bool> help = sut.on<bool>("--help", "displays help");
  };

  TEST_F(ParserHelpTestSuite, returnsHelpText) {
    std::string e;
    e += "Usage: [options] args...\n";
    e += "\n";
    e += "--name V - sets name\n";
    e += "--help - displays help\n";

    EXPECT_THAT(sut.help(), Eq(e));
  }

  TEST_F(ParserHelpTestSuite, returnsHelpTextWithAppName) {
    sut.parse(args.size(), args.data());

    std::string e;
    e += "Usage: appName [options] args...\n";
    e += "\n";
    e += "--name V - sets name\n";
    e += "--help - displays help\n";

    EXPECT_THAT(sut.help(), Eq(e));
  }

  TEST_F(ParserHelpTestSuite, returnsHelpTextWithCustomBaner) {
    sut.parse(args.size(), args.data());
    sut.banner("Usage: appName [opts] arg1 arg2");

    std::string e;
    e += "Usage: appName [opts] arg1 arg2\n";
    e += "\n";
    e += "--name V - sets name\n";
    e += "--help - displays help\n";

    EXPECT_THAT(sut.help(), Eq(e));
  }
} // namespace C8::OptionParser
