#include "bank_ocr/core/line.h"
#include <regex>
#include <unordered_map>

Line::Line() {}

const std::regex re_num("...");

Line::Line(const std::string& line) {
  std::sregex_iterator beg(line.cbegin(), line.cend(), re_num), end;
  std::for_each(beg, end, [this](auto& m) {
    nums.emplace_back(m.str());
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

  std::string recognize(const std::string& digit) {
    auto found = to_digits.find(digit);
    return found != to_digits.end() ? found->second : "?";
  }

  std::string recognize(const std::deque<std::string>& nums) {
    std::string result;
    for (auto& num : nums) {
      result += recognize(num);
    }
    return result;
  }
}

std::string Line::value() const {
  return recognize(nums);
}

namespace {
  template <typename F>
  void digits(F f) {
    for (auto& i : to_digits) {
      f(i.first);
    }
  }

  int diff(const std::string& lhs, const std::string& rhs) {
    auto num = 0;
    for (std::string::size_type i = 0; i != lhs.size(); ++i) {
      if (lhs[i] != rhs[i]) num++;
    }
    return num;
  }

  template <typename F>
  void guess(const std::string& num, F f) {
    digits([&num, &f](auto& digit) {
      if (diff(digit, num) == 1) {
        f(digit);
      }
    });
  }
}

void Line::alternatives(Alternative& alt) const {
  for (std::deque<std::string> prefix, suffix(nums); !suffix.empty();) {
    auto num = suffix.front();
    suffix.pop_front();
    guess(num, [&alt, &prefix, &suffix](auto& guess) {
      alt.accept(recognize(prefix) + recognize(guess) + recognize(suffix));
    });
    prefix.push_back(num);
  }
}
