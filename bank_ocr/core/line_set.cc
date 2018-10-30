#include "bank_ocr/core/line_set.h"
#include "bank_ocr/core/illformed_number_error.h"
#include <set>
#include <regex>
#include <algorithm>

namespace {
  void assert_true(bool expr) {
    if (!expr) throw IllformedNumberError();
  }

  template <typename F>
  void foreach(Lines& lines, F f) {
    for (auto& line : lines) {
      f(line);
    }
  }

  template <typename Pred>
  void allof(Lines& lines, Pred pred) {
    foreach(lines, [&pred](auto& line) {
      assert_true(pred(line));
    });
  }

  const std::regex re_line("^[ |_]+$");

  void checkChars(Lines& lines) {
    allof(lines, [](auto& line) {
      return std::regex_match(line, re_line);
    });
  }

  void checkLengths(Lines& lines) {
    allof(lines, [](auto& line) {
      return line.size() > 1 && line.size() % 3 == 0;
    });
  }

  void checkSameSize(Lines& lines) {
    std::set<std::string::size_type> lens;
    foreach(lines, [&lens](auto& line) {
      lens.insert(line.size());
    });
    assert_true(lens.size() == 1);
  }

  void normalize(Lines& lines) {
    std::string::size_type max = 0;
    foreach(lines, [&max](auto& line) {
      if (max < line.size()) {
        max = line.size();
      }
    });

    foreach(lines, [&max](auto& line) {
      if (line.size() < max) {
        line += std::string(max - line.size(), ' ');
      }
    });
  }
}

void LineSet::initialize(Lines& inlines) {
  for (auto& line : inlines) {
    lines.emplace_back(line);
  }
}

LineSet::LineSet(Lines& lines) {
  normalize(lines);
  checkChars(lines);
  checkLengths(lines);
  checkSameSize(lines);
  initialize(lines);
}

void LineSet::merge(Line& merged) const {
  for (auto& line : lines) {
    merged.merge(line);
  }
}
