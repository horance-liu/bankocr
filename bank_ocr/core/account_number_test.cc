#include "bank_ocr/core/account_number.h"
#include "bank_ocr/core/illformed_number_error.h"
#include "cut/cut.hpp"

USING_CUT_NS
USING_CUM_NS

FIXTURE(AccountNumberTest) {
  static void expect(Lines lines, const std::string& expected) {
    AccountNumber number;
    number.parse(lines);
    ASSERT_THAT(number.value(), eq(expected));
  }

  static void throws(Lines lines) {
    ASSERT_TRUE(throwing<IllformedNumberError>([&lines]{
      AccountNumber number;
      number.parse(lines);
    }));
  }

  TEST("1") {
    expect({
      "   ",
      "  |",
      "  |",
    }, "1");
  }

  TEST("3") {
    expect({
      " _ ",
      " _|",
      " _|",
    }, "3");
  }

  TEST("13") {
    expect({
      "    _ ",
      "  | _|",
      "  | _|",
    }, "13");
  }

  TEST("0-9") {
    expect({
      " _     _  _     _  _  _  _  _ ",
      "| |  | _| _||_||_ |_   ||_||_|",
      "|_|  ||_  _|  | _||_|  ||_| _|",
    }, "0123456789");
  }

  TEST("invalid 2") {
    expect({
      "    _  _ ",
      "  | _  _|",
      "  ||_  _|",
    }, "1?3");
  }

  TEST("contains illegal char: x") {
    throws({
      "    _  _ ",
      "  | _  _|",
      "  ||_ x_|",
    });
  }

  TEST("lines lengths not divisible by 3") {
    throws({
      "    _  _  ",
      "  | _  _| ",
      "  ||_  _| ",
    });
  }
};
