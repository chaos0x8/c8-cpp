#include "c8-sq-lite/DBCast.hpp"
#include "c8-sq-lite/SqLite3.hpp"
#include <boost/format.hpp>
#include <gmock/gmock.h>

namespace C8::SqLite {
  using namespace testing;

  struct Field {
    std::string value;

    bool operator==(const Field& other) const {
      return value == other.value;
    }
  };

  class SqLite3TestSuite : public Test {
  public:
    static void SetUpTestCase() {
      sut = std::make_unique<SqLite3>();
      sut->open(DB_FILE);

      sut->setTestMode();
      sut->execute("create table field(value string);");
    }

    void TearDown() override {
      assert(sut != nullptr);

      std::for_each(std::begin(fieldToDelete), std::end(fieldToDelete),
        std::bind(&SqLite3TestSuite::deleteField, std::placeholders::_1));
    }

    static void TearDownTestCase() {
      sut = nullptr;

      EXPECT_THAT(system(boost::str(boost::format("if [ -e %1% ]; then rm -v %1%; fi") % DB_FILE).c_str()), Eq(0));
    }

    void insertField(const Field& field, bool deleteAfter = true) {
      sut->execute(
        boost::str(boost::format("insert into field (value) values(%1%)") % DBCast::toDBFormat(field.value)));

      if (deleteAfter)
        fieldToDelete.push_back(field);
    }

    static void deleteField(const Field& field) {
      sut->execute(boost::str(boost::format("delete from field where value = %1%") % DBCast::toDBFormat(field.value)));
    }

    static std::vector<Field> loadFields() {
      SelectResult sl = sut->select("select * from field");

      std::vector<Field> result;
      std::transform(
        std::begin(sl.rows), std::end(sl.rows), std::back_inserter(result), [](const SelectResult::Row& row) {
          constexpr size_t VALUE_INDEX = 0;
          return Field{DBCast::fromDBFormat<std::string>(row[VALUE_INDEX])};
        });
      return result;
    }

    const Field FIELD_1{"cat"};
    const Field FIELD_2{"dog"};
    const Field FIELD_3{"tiger"};

    static const std::string DB_FILE;

    static std::unique_ptr<SqLite3> sut;
    std::stringstream outputStream;

  private:
    std::vector<Field> fieldToDelete;
  };

  const std::string SqLite3TestSuite::DB_FILE = "test.db";
  std::unique_ptr<SqLite3> SqLite3TestSuite::sut;

  TEST_F(SqLite3TestSuite, selectsValue) {
    insertField(FIELD_1);

    ASSERT_THAT(loadFields(), UnorderedElementsAre(FIELD_1));
  }

  TEST_F(SqLite3TestSuite, sucessfulTransaction) {
    const bool transactionStatus = sut->transaction(
      [this]() -> void {
        insertField(FIELD_1);
        insertField(FIELD_2);
      },
      outputStream);

    ASSERT_TRUE(transactionStatus);
    ASSERT_THAT(loadFields(), UnorderedElementsAre(FIELD_1, FIELD_2));
  }

  TEST_F(SqLite3TestSuite, failedTransaction) {
    insertField(FIELD_1);

    const bool transactionStatus = sut->transaction(
      [this]() -> void {
        insertField(FIELD_2, false);
        insertField(FIELD_3, false);
        sut->execute("insert into not_existing (field) ('value')");
      },
      outputStream);

    ASSERT_FALSE(transactionStatus);
    ASSERT_THAT(loadFields(), UnorderedElementsAre(FIELD_1));
  }

  TEST_F(SqLite3TestSuite, failedTransactionWithUserException) {
    insertField(FIELD_1);

    const bool transactionStatus = sut->transaction(
      [this]() -> void {
        insertField(FIELD_2, false);
        insertField(FIELD_3, false);
        throw std::exception();
      },
      outputStream);

    ASSERT_FALSE(transactionStatus);
    ASSERT_THAT(loadFields(), UnorderedElementsAre(FIELD_1));
  }
} // namespace C8::SqLite
