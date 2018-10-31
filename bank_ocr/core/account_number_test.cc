#include "bank_ocr/core/account_number.h"
#include "cut/cut.hpp"
#include <stdexcept>

USING_CUT_NS
USING_CUM_NS

FIXTURE(AccountNumberTest) {
  static void expect(std::vector<std::string> lines, const std::string& expected) {
    ASSERT_THAT(AccountNumber(lines).str(), eq(expected));
  }

  static void throws(std::vector<std::string> lines) {
    ASSERT_TRUE(throwing<std::invalid_argument>([&lines]{
      AccountNumber number(lines);
    }));
  }

  TEST("no guess: 711111111") {
    expect({
      " _                         ",
      "  |  |  |  |  |  |  |  |  |",
      "  |  |  |  |  |  |  |  |  |",
    }, "711111111");
  }

  TEST("only one guess: 111111111") {
    expect({
      "                           ",
      "  |  |  |  |  |  |  |  |  |",
      "  |  |  |  |  |  |  |  |  |",
    }, "711111111");
  }

  TEST("only one guess: 777777777") {
    expect({
      " _  _  _  _  _  _  _  _  _ ",
      "  |  |  |  |  |  |  |  |  |",
      "  |  |  |  |  |  |  |  |  |",
    }, "777777177");
  }

  TEST("contains one illegible digit: 0?0000051") {
    expect({
      " _     _  _  _  _  _  _    ",
      "| || || || || || || ||_   |",
      "|_||_||_||_||_||_||_| _|  |",
    }, "000000051");
  }

  TEST("contains one illegible digit: 49086771?") {
    expect({
      "    _  _  _  _  _  _     _ ",
      "|_||_|| ||_||_   |  |  | _ ",
      "  | _||_||_||_|  |  |  | _|",
    }, "490867715");
  }

  TEST("ILL: contains one illegible digits, but no alternative: 49006771?") {
    expect({
      "    _  _  _  _  _  _     _ ",
      "|_||_|| || ||_   |  |  | _ ",
      "  | _||_||_||_|  |  |  | _|",
    }, "49006771? ILL");
  }

  TEST("ILL: contains two illegible digits: ?9086771?") {
    expect({
      "    _  _  _  _  _  _     _ ",
      "|_||_|| ||_||_   |  |  | _ ",
      "    _||_||_||_|  |  |  | _|",
    }, "?9086771? ILL");
  }

  TEST("ERR(no valid alternatives): 444444444") {
    expect({
      "                           ",
      "|_||_||_||_||_||_||_||_||_|",
      "  |  |  |  |  |  |  |  |  |",

    }, "444444444 ERR");
  }

  TEST("AMB: 888888888") {
    expect({
      " _  _  _  _  _  _  _  _  _ ",
      "|_||_||_||_||_||_||_||_||_|",
      "|_||_||_||_||_||_||_||_||_|",
    }, "888888888 AMB [888886888, 888888988, 888888880]");
  }


  TEST("contains illegal char: *") {
    throws({
      " _  _  _  _  _  _  _  _  _ ",
      "|_||_||_||_||_||_||_||_||_|",
      "|_||_||_||_|*_||_||_||_||_|",
    });
  }

  TEST("length is not the same") {
    throws({
      " _  _  _  _  _  _  _  _  _ ",
      "|_||_||_||_||_||_||_||_||_| ",
      "|_||_||_||_||_||_||_||_||_|  ",
    });
  }

  TEST("ERR: invalid length(==10)") {
    expect({
      " _  _  _  _  _  _  _  _  _  _ ",
      "|_||_||_||_||_||_||_||_||_||_|",
      "|_||_||_||_||_||_||_||_||_||_|",
    }, "8888888888 ERR");
  }
};
