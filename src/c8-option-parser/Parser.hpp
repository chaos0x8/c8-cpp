#pragma once

#include "Args.hpp"
#include "Option.hpp"
#include <deque>
#include <memory>
#include <string>
#include <vector>

namespace C8::OptionParser {
  struct Parser {
    Parser() = default;
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;

    void parse(int argc, char** argv);
    void parse(int argc, const char** argv);
    void parse(std::vector<std::string> args);
    std::string_view name() const;
    std::string help() const;
    void banner(std::string_view);
    std::string_view banner() const;

    Args args() const {
      return Args(args_);
    }

    template <class T>
    Option<T> on(std::string_view name, std::string_view description) {
      verifyOptionName(name);

      auto option = std::make_shared<Detail::TypedOption<T>>(name, description);
      options_.emplace_back(option);
      return Option<T>(std::move(option));
    }

    template <size_t Arity = 0, class F>
    void on(std::string_view name, std::string_view description, F&& fun) {
      verifyOptionName(name);

      auto option = std::make_shared<Detail::LambdaOption<Arity, F>>(
        name, description, std::move(fun));
      options_.emplace_back(std::move(option));
    }

  private:
    bool isOptionNameValid(std::string_view) const;
    void verifyOptionName(std::string_view) const;

    std::string name_;
    std::string banner_;
    std::deque<std::string> args_;
    std::vector<std::shared_ptr<Detail::Option>> options_;
  };
} // namespace C8::OptionParser
