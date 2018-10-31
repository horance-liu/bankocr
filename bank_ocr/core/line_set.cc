#include "bank_ocr/core/line_set.h"
#include "bank_ocr/core/number_format_error.h"
#include <set>
#include <regex>

namespace {
  void assertTrue(bool expr, const char* msg) {
    if (!expr) throw NumberFormatError(msg);
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
      assertTrue(pred(line), msg);
    });
  }

  const std::regex re_line("^[ |_]+$");

  void checkChars(LineSet::Lines& lines) {
    allof(lines, "should contain [ |_]", [](auto& line) {
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
    assertTrue(lens.size() == 1, "length should be same");
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

  bool allEmpty(const LineSet::Lines& lines) {
    return std::all_of(lines.begin(), lines.end(), [](auto& line) {
      return line.empty();
    });
  }
}

void LineSet::save(const Lines& inlines) {
  for (auto& line : inlines) {
    lines.emplace_back(line);
  }
}

LineSet::LineSet(Lines& lines) : empty(allEmpty(lines)) {
  if (!empty) {
    normalize(lines);
    checkChars(lines);
    checkLengths(lines);
    checkSameSize(lines);
    save(lines);
  }
}

bool LineSet::isEmpty() const {
  return empty;
}

void LineSet::merge(Line& merged) const {
  for (auto& line : lines) {
    merged.merge(line);
  }
}
