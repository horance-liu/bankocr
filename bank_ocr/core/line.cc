#include "bank_ocr/core/line.h"
#include <regex>
#include <unordered_map>

const std::regex re_num("...");

Line::Line(const std::string& line) {
  std::sregex_iterator beg(line.cbegin(), line.cend(), re_num), end;
  std::for_each(beg, end, [this](auto& m) {
    nums.push_back(m.str());
  });
}

void Line::reset() {
  nums.clear();
}

void Line::merge(const Line& rhs) {
  if (nums.empty()) {
    nums = rhs.nums;
    return;
  }

  auto i2 = rhs.nums.begin();
  for (auto i1 = nums.begin(); i1 != nums.end(); i1++) {
    *i1 += *i2;
    i2++;
  }
}

namespace {
  const std::unordered_map<std::string, std::string> to_digits = {
    {
      " _ "
      "| |"
      "|_|", "0"
    },

    {
      "   "
      "  |"
      "  |", "1"
    },

    {
      " _ "
      " _|"
      "|_ ", "2"
    },

    {
      " _ "
      " _|"
      " _|", "3"
    },

    {
      "   "
      "|_|"
      "  |", "4"
    },

    {
      " _ "
      "|_ "
      " _|", "5"
    },

    {
      " _ "
      "|_ "
      "|_|", "6"
    },

    {
      " _ "
      "  |"
      "  |", "7"
    },

    {
      " _ "
      "|_|"
      "|_|", "8"
    },

    {
      " _ "
      "|_|"
      " _|", "9"
    },
  };

  std::string recognize(const std::string& scanned) {
    auto found = to_digits.find(scanned);
    return found != to_digits.end() ? found->second : "?";
  }
}

void Line::join(std::string& result) const {
  for (auto& num : nums) {
    result += recognize(num);
  }
}
