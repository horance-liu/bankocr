#include "bankocr/str_utils.h"
#include "cut/cut.hpp"

USING_CUT_NS
USING_CUM_NS

using namespace std::string_literals;

FIXTURE(StrUtilsTest) {
  TEST("join") {
    const char* strs[] = {"1", "2", "3"};
    ASSERT_THAT(str_utils::join(strs, strs +3, ","), eq("1,2,3"s));
  }

  TEST("rtrim") {
    ASSERT_THAT(str_utils::rtrim("x   ", 0), eq("x"s));
  }

  TEST("diff") {
    ASSERT_THAT(str_utils::diff("xxx", "yyy"), eq(3));
  }
};
