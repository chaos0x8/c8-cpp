#pragma once

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace C8::SqLite {
  struct FirstLetterHash {
    size_t operator()(const std::string& text) const {
      return static_cast<size_t>(text[0]);
    }
  };

  class SelectResult {
  public:
    using Row = std::vector<std::string>;
    using size_type = std::vector<Row>::size_type;

    bool empty() const {
      return rows.empty();
    }

    size_type size() const {
      return rows.size();
    }

    void push_back(Row row) {
      rows.push_back(std::move(row));
    }

    void addColumn(const std::string& column, size_t index) {
      _columnMap[column] = index;
    }

    std::string& at(size_t index, const std::string& key) {
      return rows[index][_columnMap.at(key)];
    }

    const std::string& at(size_t index, const std::string& key) const {
      return rows[index][_columnMap.at(key)];
    }

    template <class... Args>
    auto mapColumns(Args&&... args) const {
      return std::make_tuple(_columnMap.at(args)...);
    }

    std::vector<Row> rows;

  private:
    std::unordered_map<std::string, size_t, FirstLetterHash> _columnMap;
  };
} // namespace C8::SqLite
