#include "bank_ocr/core/line.h"
#include <regex>
#include <unordered_map>

const std::regex re_num("...");

Line::Line(const std::string& line) {
  std::sregex_iterator beg(line.begin(), line.end(), re_num), end;
  std::for_each(beg, end, [this](auto& m) {
    nums.emplace_back(m.str());
  });
}

void Line::reset() {
  nums.clear();
}

void Line::zip(const Line& rhs) {
  auto i2 = rhs.nums.begin();
  for (auto i1 = nums.begin(); i1 != nums.end(); i1++) {
    *i1 += *i2;
    i2++;
  }
}

void Line::merge(const Line& rhs) {
  if (nums.empty()) {
    nums = rhs.nums;
  } else {
    zip(rhs);
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

  std::string to(const std::string& digit) {
    auto found = to_digits.find(digit);
    return found != to_digits.end() ? found->second : "?";
  }

  std::string to(const std::deque<std::string>& nums) {
    std::string result;
    for (auto& num : nums) {
      result += to(num);
    }
    return result;
  }
}

std::string Line::value() const {
  return to(nums);
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

  template <typename F, int confidence = 1>
  void guess(const std::string& num, F f) {
    digits([&num, &f](auto& digit) {
      if (diff(digit, num) == confidence) {
        f(digit);
      }
    });
  }
}

// NOTE: performance is not good, should not copy it.
void Line::alternatives(Alternative& alt) const {
  for (std::deque<std::string> prefix, suffix(nums); !suffix.empty();) {
    auto num = suffix.front();
    suffix.pop_front();
    guess(num, [&alt, &prefix, &suffix](auto& digit) {
      alt.accept(to(prefix) + to(digit) + to(suffix));
    });
    prefix.push_back(num);
  }
}
