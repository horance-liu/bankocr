#include "bank_ocr/core/line_set.h"
#include "bank_ocr/core/illformed_number_error.h"
#include <set>
#include <regex>
#include <algorithm>
#include <iostream>

namespace {
  void assert_true(bool expr, const char* msg) {
    if (!expr) throw IllformedNumberError(msg);
  }

  template <typename F>
  void foreach(LineSet::Lines& lines, F f) {
    for (auto& line : lines) {
      f(line);
    }
  }

  template <typename Pred>
  void allof(LineSet::Lines& lines, const char* msg, Pred pred) {
    foreach(lines, [&pred, msg](auto& line) {
      assert_true(pred(line), msg);
    });
  }

  const std::regex re_line("^[ |_]+$");

  void checkChars(LineSet::Lines& lines) {
    allof(lines, "should contain only [ |_]", [](auto& line) {
      return std::regex_match(line, re_line);
    });
  }

  void checkLengths(LineSet::Lines& lines) {
    allof(lines, "length should be times of 3", [](auto& line) {
      return line.size() > 1 && line.size() % 3 == 0;
    });
  }

  void checkSameSize(LineSet::Lines& lines) {
    std::set<std::string::size_type> lens;
    foreach(lines, [&lens](auto& line) {
      lens.insert(line.size());
    });
    assert_true(lens.size() == 1, "length should be the same");
  }

  void normalize(LineSet::Lines& lines) {
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

  bool isAllEmpty(LineSet::Lines& lines) {
    auto result = true;
    foreach(lines, [&result](auto& line) {
      if (!line.empty()) result = false;
    });
    return result;
  }
}

void LineSet::initialize(Lines& inlines) {
  for (auto& line : inlines) {
    lines.emplace_back(line);
  }
}

LineSet::LineSet(Lines& lines) : empty(isAllEmpty(lines)) {
  if (empty) return;
  normalize(lines);
  checkChars(lines);
  checkLengths(lines);
  checkSameSize(lines);
  initialize(lines);
}

bool LineSet::isEmpty() const {
  return empty;
}

void LineSet::merge(Line& merged) const {
  for (auto& line : lines) {
    merged.merge(line);
  }
}
