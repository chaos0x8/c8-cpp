#include "c8-common/StrongType.hpp"
#include <gmock/gmock.h>

namespace C8::Common {
  using namespace testing;

  struct TestStrongType : public Test {
    using Type = StrongType<uint32_t, struct TypeTag>;

    Type sut{42};
  };

  TEST_F(TestStrongType, shouldReturnSameValue) {
    ASSERT_THAT(*sut, Eq(42));
  }

  TEST_F(TestStrongType, shouldReturnSameValueConst) {
    ASSERT_THAT(Const(*sut), Eq(42));
  }

  TEST_F(TestStrongType, shouldModifyValueDereference) {
    *sut = 10;

    ASSERT_THAT(*sut, Eq(10));
  }

  TEST_F(TestStrongType, shouldModifyValueAssignOperator) {
    auto other = Type(12);

    sut = other;

    ASSERT_THAT(*sut, Eq(12));
  }

  TEST_F(TestStrongType, shouldModifyValueMoveOperator) {
    sut = Type(10);

    ASSERT_THAT(*sut, Eq(10));
  }

  TEST_F(TestStrongType, shouldCopy) {
    auto other = sut;

    ASSERT_THAT(*other, Eq(42));
    ASSERT_THAT(Type(sut), Eq(Type(42)));
  }

  TEST_F(TestStrongType, shouldCompare) {
    ASSERT_THAT(sut, Eq(Type(42)));
    ASSERT_THAT(sut, Ne(Type(30)));
    ASSERT_THAT(sut, Gt(Type(30)));
    ASSERT_THAT(sut, Ge(Type(30)));
    ASSERT_THAT(sut, Lt(Type(100)));
    ASSERT_THAT(sut, Le(Type(100)));
  }
} // namespace C8::Common
