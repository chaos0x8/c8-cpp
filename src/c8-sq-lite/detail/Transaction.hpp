#pragma once

namespace C8::SqLite::Detail {
  enum class TransactionState : uint8_t { None, Started, Commited };

  struct Transaction {
    explicit Transaction(SqLite3& sqLite) : _sqLite(sqLite) {}
    Transaction(const Transaction&) = delete;

    ~Transaction() {
      if (_state == TransactionState::Started)
        _sqLite.execute("rollback");
    }

    Transaction& operator=(const Transaction&) = delete;

    void commit(const std::function<void()> operation) {
      _sqLite.execute("begin transaction");
      _state = TransactionState::Started;

      operation();

      _sqLite.execute("commit transaction");
      _state = TransactionState::Commited;
    }

  private:
    SqLite3& _sqLite;
    TransactionState _state = TransactionState::None;
  };
} // namespace C8::SqLite::Detail
