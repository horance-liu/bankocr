#include "bankocr/account.h"
#include "cut/cut.hpp"
#include <stdexcept>

USING_CUT_NS
USING_CUM_NS

FIXTURE(AccountTest) {
  static void expect(Account::Lines lines, const std::string& expected) {
    ASSERT_THAT(Account(lines).str(), eq(expected));
  }

  static void throws(Account::Lines lines) {
    ASSERT_TRUE(throwing<std::invalid_argument>([&lines]{
      Account number(lines);
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

  TEST("will append missing space at end lines") {
    expect({
      "",  // missing spaces.
      "  |  |  |  |  |  |  |  |  |",
      "  |  |  |  |  |  |  |  |  |",
    }, "711111111");
  }

  TEST("should be 3 lines") {
    throws({
      "  |  |  |  |  |  |  |  |  |  ",
      "  |  |  |  |  |  |  |  |  |  ",
    });
  }

  TEST("it contains only 8 digits, and will append missing spaces at end lines") {
    expect({
      "    _  _     _  _  _  _ ",
      "  | _| _||_||_ |_   ||_|",
      "  ||_  _|  | _||_|  ||_|",
    }, "12345678? ILL");
  }

  TEST("will rtrim all blanks at end of lines") {
    expect({
      " _                            ",
      "  |  |  |  |  |  |  |  |  |   ",
      "  |  |  |  |  |  |  |  |  |   ",
    }, "711111111");
  }

  TEST("will not rtrim non-blanks at end of lines") {
    throws({
      " _     _  _     _  _  _  _  _ ",
      "| |  | _| _||_||_ |_   ||_||_|",
      "|_|  ||_  _|  | _||_|  ||_| _|",
    });
  }

  TEST("will not ltrim blanks at begin of lines") {
    throws({
      "   _                         ",
      "    |  |  |  |  |  |  |  |  |",
      "    |  |  |  |  |  |  |  |  |",
    });
  }

  TEST("line should be only [ |_], but it contains x") {
    throws({
      " _  _  _  _  _  _  _  _  _ ",
      "|_||_||_||_||_||_||_||_||_|",
      "|_||_||_||_|x_||_||_||_||_|",
    });
  }
};
