#include "bankocr/check_sum.h"

namespace {
  int sum(const std::string& value) {
    auto result = 0;
    for (std::string::size_type i = 0; i != value.size(); ++i) {
      result += (value[i] - '0') * (value.size() - i);
    }
    return result;
  }

  int checksum(const std::string& value) {
    return sum(value) % 11;
  }
}

bool check(const std::string& value) {
  return value.size() == 9 && checksum(value) == 0;
}
