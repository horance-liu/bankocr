#include "bank_ocr/core/check_sum.h"
#include "cut/cut.hpp"

USING_CUT_NS
USING_CUM_NS

FIXTURE(CheckSumTest) {
  TEST("ok") {
    ASSERT_TRUE(check("000000000"));
    ASSERT_TRUE(check("000000051"));
  }

  TEST("err") {
    ASSERT_FALSE(check("111111111"));
  }

  TEST("err: invalid size(!=9)") {
    ASSERT_FALSE(check("00000000"));
    ASSERT_FALSE(check("0000000000"));
  }
};
