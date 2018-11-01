#include "bankocr/check_sum.h"
#include "bankocr/str_utils.h"

namespace {

int sum(const std::string& value) {
  auto result = 0;
  str_utils::foreach(value, [&value, &result](auto ch, auto i) {
    result += (ch - '0') * (value.size() - i);
  }); 
  return result;
}

int checksum(const std::string& value) {
  return sum(value) % 11;
}

}

bool check(const std::string& value) {
  return value.size() == 9 && checksum(value) == 0;
}
