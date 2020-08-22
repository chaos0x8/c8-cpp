#pragma once

#include <stdexcept>

namespace C8::OptionParser {
  struct Error : public std::runtime_error {
    Error() : std::runtime_error("OptionParser::Error") {}
    Error(std::string_view msg)
      : std::runtime_error(
          std::string("OptionParser::Error ") + std::string(msg)) {}
  };

  struct InvalidOptionNameError : public Error {
    InvalidOptionNameError(std::string_view name)
      : Error(std::string("InvalidOptionNameError '") + std::string(name) +
              std::string("'")) {}
  };

  struct UnknownOptionError : public Error {
    UnknownOptionError(std::string_view name)
      : Error(std::string("UnknownOptionError '") + std::string(name) +
              std::string("'")) {}
  };

  struct MissingArgumentError : public Error {
    MissingArgumentError() : Error("MissingArgumentError") {}
  };
} // namespace C8::OptionParser
