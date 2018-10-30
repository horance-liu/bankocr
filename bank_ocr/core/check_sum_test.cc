#include "bank_ocr/core/check_sum.h"
#include "cut/cut.hpp"

USING_CUT_NS
USING_CUM_NS

FIXTURE(CheckSumTest) {
  TEST("ok") {
    ASSERT_TRUE(check("000000000"));
    ASSERT_TRUE(check("000000051"));
    ASSERT_TRUE(check("123456789"));
    ASSERT_TRUE(check("200800000"));
    ASSERT_TRUE(check("333393333"));
    ASSERT_TRUE(check("490867715"));
    ASSERT_TRUE(check("664371485"));
    ASSERT_TRUE(check("711111111"));
    ASSERT_TRUE(check("777777177"));
  }

  TEST("err") {
    ASSERT_FALSE(check("111111111"));
    ASSERT_FALSE(check("490067715"));
    ASSERT_FALSE(check("664371495"));
  }

  TEST("err: invalid size") {
    ASSERT_FALSE(check("00000000"));
    ASSERT_FALSE(check("0000000000"));
  }
};
