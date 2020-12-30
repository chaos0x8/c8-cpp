/*!
 *  \author <https://github.com/chaos0x8>
 *  \copyright
 *  Copyright (c) 2015 - 2016, <https://github.com/chaos0x8>
 *
 *  \copyright
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  \copyright
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "c8-sq-lite/SqLite3.hpp"
#include "c8-common/Format.hpp"
#include "c8-sq-lite/detail/Transaction.hpp"
#include "c8-sq-lite/errors.hpp"

namespace C8::SqLite {
  void SqLite3::SqLiteDeleter::operator()(sqlite3* db) const {
    sqlite3_close(db);
  }

  void SqLite3::SqLiteDeleter::operator()(void* mem) const {
    sqlite3_free(mem);
  }

  void SqLite3::open(const std::string& fileName) {
    sqlite3* tmpDb = 0;
    int err = sqlite3_open(fileName.c_str(), &tmpDb);
    db = std::unique_ptr<sqlite3, SqLiteDeleter>(tmpDb, SqLiteDeleter());

    if (err != SQLITE_OK || operator bool() == false) {
      throw Errors::Error(Common::format("Cannot read data base '%s', error code: %d", fileName, err));
    }
  }

  SelectResult SqLite3::select(const std::string& select) {
    std::pair<SelectResult, bool> selData{SelectResult{}, false};

    char* rawErrorMsg = 0;
    int err = sqlite3_exec(db.get(), select.c_str(), SqLite3::selectCallBack, &selData, &rawErrorMsg);
    if (err != SQLITE_OK) {
      std::unique_ptr<char, SqLiteDeleter> errorMsg(rawErrorMsg, SqLiteDeleter());
      throw Errors::Error(Common::format("Error during select[%d]: '%s'", err, errorMsg.get()));
    }

    return std::move(selData.first);
  }

  void SqLite3::execute(const std::string& query) {
    char* rawErrorMsg = 0;
    int err = sqlite3_exec(db.get(), query.c_str(), 0, 0, &rawErrorMsg);
    if (err != SQLITE_OK) {
      std::unique_ptr<char, SqLiteDeleter> errorMsg(rawErrorMsg, SqLiteDeleter());
      throw Errors::Error(Common::format("Error during execute[%d]: '%s'", err, errorMsg.get()));
    }
  }

  int64_t SqLite3::getLastInsertedId() {
    return sqlite3_last_insert_rowid(db.get());
  }

  bool SqLite3::transaction(std::function<void()> operation, std::ostream& out) {
    try {
      Detail::Transaction t(*this);
      t.commit(operation);
    } catch (std::exception& e) {
      out << "Transaction failed: " << e.what() << std::endl;
      return false;
    }
    return true;
  }

  void SqLite3::setTestMode() {
    execute("PRAGMA synchronous = OFF;"
            "PRAGMA journal_mode = MEMORY;");
  }

  SqLite3::operator bool() const {
    return static_cast<bool>(db);
  }

  int SqLite3::selectCallBack(void* data, int argc, char** argv, char** colName) {
    if (argc < 0) {
      return 0;
    }

    auto result = static_cast<std::pair<SelectResult, bool>*>(data);

    if (!result->second) {
      for (size_t i = 0; i < static_cast<size_t>(argc); ++i) {
        result->first.addColumn(colName[i], i);
      }
    }

    SelectResult::Row newRow;
    newRow.reserve(static_cast<size_t>(argc));
    for (auto ptr = argv; ptr != argv + argc; ++ptr) {
      newRow.emplace_back(*ptr ? *ptr : std::string());
    }

    result->first.push_back(std::move(newRow));
    result->second = true;

    return 0;
  }
} // namespace C8::SqLite
