#include "bank_ocr/core/check_sum.h"

namespace {
  int sum(const std::string& value) {
    auto result = 0;
    for (decltype(value.size()) i = 0; i != value.size(); ++i) {
      result += (value[i] - '0') * (value.size() - i);
    }
    return result;
  }

  int check_sum(const std::string& value) {
    return sum(value) % 11;
  }
}

bool check(const std::string& value) {
  return value.size() == 9 && check_sum(value) == 0;
}
