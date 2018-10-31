#include "bank_ocr/core/line_set.h"
#include "bank_ocr/core/number_format_error.h"
#include "cut/cut.hpp"

USING_CUT_NS
USING_CUM_NS

FIXTURE(LineSetTest) {
  static void throws(LineSet::Lines lines) {
    ASSERT_TRUE(throwing<NumberFormatError>([&lines]{
      LineSet set(lines);
    }));
  }

  TEST("| is not l") {
    throws({
      "   ",
      "  l",
      "  |"
    });
  }

  TEST("length is not times of 3") {
    throws({
        " _  ",
        "  | ",
        "  | "
    });
  }

  TEST("length is not same") {
    throws({
      " _ ",
      "  | ",
      "  |  "
    });
  }
};
