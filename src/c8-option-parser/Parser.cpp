#include "Parser.hpp"
#include "Error.hpp"
#include <algorithm>
#include <regex>
#include <sstream>

namespace C8::OptionParser {
  namespace Detail {
    template <class T> std::vector<std::string> toVec(int argc, T** argv) {
      std::vector<std::string> args;

      for (int i = 1; i < argc; ++i) {
        args.emplace_back(argv[i]);
      }

      return args;
    }
  } // namespace Detail

  void Parser::parse(int argc, char** argv) {
    parse(Detail::toVec(argc, argv));

    if (argc >= 1) {
      name_ = argv[0];
    }
  }

  void Parser::parse(int argc, const char** argv) {
    parse(Detail::toVec(argc, argv));

    if (argc >= 1) {
      name_ = argv[0];
    }
  }

  void Parser::parse(std::vector<std::string> args) {
    std::shared_ptr<Detail::Option> opt;
    bool verifyUnknownArguments = true;

    for (auto& arg : args) {
      if (arg == "--") {
        verifyUnknownArguments = false;
      } else {
        auto kt = std::find_if(std::begin(options_), std::end(options_),
          [&arg](const auto& o) { return o->name() == arg; });

        if (kt != std::end(options_)) {
          opt = *kt;

          if (opt->arity() == 0u) {
            opt->set("");
            opt = nullptr;
          }
        } else {
          if (opt) {
            opt->set(arg);
            if (opt->arity() == 1u) {
              opt = nullptr;
            }
          } else {
            if (verifyUnknownArguments and isOptionNameValid(arg)) {
              throw UnknownOptionError(arg);
            }

            args_.emplace_back(std::move(arg));
          }
        }
      }
    }
  }

  std::string_view Parser::name() const {
    return name_;
  }

  std::string Parser::help() const {
    std::stringstream ss;
    if (banner_.size() > 0) {
      ss << banner_ << "\n";
    } else {
      if (name_.size() > 0) {
        ss << "Usage: " << name_ << " [options] args...\n";
      } else {
        ss << "Usage: [options] args...\n";
      }
    }
    ss << "\n";

    for (const auto& opt : options_) {
      if (opt->arity() == 0) {
        ss << opt->name() << " - " << opt->description() << "\n";
      } else {
        ss << opt->name() << " V - " << opt->description() << "\n";
      }
    }

    return ss.str();
  }

  void Parser::banner(std::string_view value) {
    banner_ = value;
  }

  std::string_view Parser::banner() const {
    return banner_;
  }

  bool Parser::isOptionNameValid(std::string_view name) const {
    std::cmatch m;

    if (std::regex_match(name.data(), m, std::regex("^-\\w+"))) {
      return true;
    }

    if (std::regex_match(name.data(), m, std::regex("^--\\w+"))) {
      return true;
    }

    return false;
  }

  void Parser::verifyOptionName(std::string_view name) const {
    if (not isOptionNameValid(name)) {
      throw InvalidOptionNameError(name);
    }
  }
} // namespace C8::OptionParser
