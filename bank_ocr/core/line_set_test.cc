#include "bank_ocr/core/line_set.h"
#include "bank_ocr/core/illformed_number_error.h"
#include "cut/cut.hpp"

USING_CUT_NS
USING_CUM_NS

FIXTURE(LineSetTest) {
  static void throws(LineSet::Lines lines) {
    ASSERT_TRUE(throwing<IllformedNumberError>([&lines]{
      LineSet set(lines);
    }));
  }

  TEST("| is not [1l!]") {
    throws({
        "  1",
        "  l",
        "  !"
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
