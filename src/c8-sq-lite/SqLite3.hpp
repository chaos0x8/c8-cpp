#pragma once
#include "c8-sq-lite/ISqLite.hpp"
#include <cstdint>
#include <memory>
#include <sqlite3.h>
#include <string>
#include <vector>

namespace C8::SqLite {
  class SqLite3 : public ISqLite {
  public:
    void open(const std::string& fileName) override;
    SelectResult select(const std::string& select) override;
    void execute(const std::string& query) override;
    int64_t getLastInsertedId() override;

    bool transaction(std::function<void()> operation, std::ostream& = std::cerr) override;

    void setTestMode() override;

    operator bool() const override;

  private:
    class SqLiteDeleter {
    public:
      void operator()(sqlite3* db) const;
      void operator()(void* mem) const;
    };

    static int selectCallBack(void* data, int argc, char** argv, char** colName);

    std::unique_ptr<sqlite3, SqLiteDeleter> db;
  };
} // namespace C8::SqLite
