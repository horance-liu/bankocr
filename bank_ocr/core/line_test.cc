#include "bank_ocr/core/line.h"
#include "cut/cut.hpp"
#include <array>

USING_CUT_NS
USING_CUM_NS

FIXTURE(LineTest) {
  using Lines = std::vector<const char*>;

  static Line line(const Lines& lines) {
    Line merged;
    for (auto& line : lines) {
      merged.merge(Line(line));
    }
    return merged;
  }

  static void expect(const Lines& lines, const std::string& value) {
    ASSERT_THAT(line(lines).value(), eq(value));
  }

  TEST("single digit") {
    expect({
      "   ",
      "  |",
      "  |",
    }, "1");
  }

  TEST("| is not !") {
    expect({
      "   ",
      "  !",
      "  |",
    }, "?");
  }

  TEST("| is not 1") {
    expect({
      "   ",
      "  1",
      "  |",
    }, "?");
  }

  TEST("| is not l") {
    expect({
      "   ",
      "  l",
      "  |",
    }, "?");
  }

  TEST("is not 1") {
    expect({
      "  |",
      "  |",
      "  |",
    }, "?");

    expect({
      "   ",
      "|  ",
      "|  ",
    }, "?");

    expect({
      "  |",
      "  |",
      "   ",
    }, "?");

    expect({
      "   ",
      " | ",
      " | ",
    }, "?");
  }

  TEST("is not 2: - is not _") {
    expect({
      " - ",
      " _|",
      "|_ ",
    }, "?");
  }

  TEST("all blank") {
    expect({
      "   ",
      "   ",
      "   ",
    }, "?");
  }

  TEST("1024: programmer's lucky number") {
    expect({
      "    _  _    ",
      "  || | _||_|",
      "  ||_||_   |",
    }, "1024");
  }

  TEST("contains illegible digit: x") {
    expect({
      "    _  _ ",
      "  | _| _|",
      "  ||_ x_|",
    }, "12?");
  }

  TEST("all digits") {
    expect({
      " _     _  _     _  _  _  _  _ ",
      "| |  | _| _||_||_ |_   ||_||_|",
      "|_|  ||_  _|  | _||_|  ||_| _|",
    }, "0123456789");
  }

  struct Collector : Alternative {
    void matches(const std::vector<std::string>& expected) const {
      ASSERT_THAT(alts, eq(expected));
    }

  private:
    void accept(const std::string& alt) override {
      alts.emplace_back(alt);
    }

  private:
    std::vector<std::string> alts;
  };

  TEST("alternatives") {
    Collector collector;
    line({
      "                           ",
      "  |  |  |  |  |  |  |  |  |",
      "  |  |  |  |  |  |  |  |  |",
    }).alternatives(collector);

    collector.matches({
      "711111111",
      "171111111",
      "117111111",
      "111711111",
      "111171111",
      "111117111",
      "111111711",
      "111111171",
      "111111117",
    });
  }
};
