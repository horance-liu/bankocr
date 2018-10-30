#include "bank_ocr/core/line.h"
#include "cut/cut.hpp"

USING_CUT_NS
USING_CUM_NS

FIXTURE(LineTest) {
  static Line line(const char* l1, const char* l2, const char* l3) {
    Line line1(l1);
    Line line2(l2);
    Line line3(l3);

    Line line;
    line.merge(line1);
    line.merge(line2);
    line.merge(line3);
    return line;
  }

  static void expect(const char* l1, const char* l2, const char* l3, const char* value) {
    ASSERT_THAT(line(l1, l2, l3).value(), eq(std::string(value)));
  }

  TEST("single digit") {
    expect(
        " _ ",
        "  |",
        "  |",
        "7"
    );
  }

  TEST("double digits") {
    expect(
        " _  _ ",
        "  |  |",
        "  |  |",
        "77"
    );
  }

  TEST("full digits") {
    expect(
        " _  _  _  _  _  _  _  _  _ ",
        "  |  |  |  |  |  |  |  |  |",
        "  |  |  |  |  |  |  |  |  |",
        "777777777"
    );
  }

  TEST("alternatives") {
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

    Collector collector;

    line(
        "                           ",
        "  |  |  |  |  |  |  |  |  |",
        "  |  |  |  |  |  |  |  |  |"
    ).alternatives(collector);

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
