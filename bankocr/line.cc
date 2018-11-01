#include "bankocr/line.h"
#include "bankocr/str_utils.h"

#include <regex>
#include <unordered_map>

Line::Line(const std::string& line) {
  static const std::regex re("...");
  std::sregex_iterator beg(line.begin(), line.end(), re), end;
  std::for_each(beg, end, [this](auto& m) {
    nums.emplace_back(m.str());
  });
}

void Line::reset() {
  nums.clear();
}

inline void Line::zip(const Line& rhs) {
  auto dst = rhs.nums.begin();
  for (auto& src : nums) {
    src += *dst++;
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

using Nums = std::deque<std::string>;

std::string to(const Nums& nums) {
  std::string result;
  for (auto& num : nums) {
    result += to(num);
  }
  return result;
}

template <typename F>
void digits(F f) {
  for (auto& i : to_digits) {
    f(i.first);
  }
}

template <typename F, int confidence = 1>
void guess(const std::string& num, F f) {
  digits([&num, &f](auto& digit) {
    auto degree = str_utils::diff(digit, num);
    if (degree > 0 && degree <= confidence) {
      f(digit);
    }
  });
}

}

void Line::alternatives(Alternative& alt) const {
  for (Nums prefix, suffix(nums); !suffix.empty();) {
    auto num = suffix.front();
    suffix.pop_front();
    guess(num, [&alt, &prefix, &suffix](auto& digit) {
      alt.accept(to(prefix) + to(digit) + to(suffix));
    });
    prefix.push_back(num);
  }
}

std::string Line::value() const {
  return to(nums);
}
