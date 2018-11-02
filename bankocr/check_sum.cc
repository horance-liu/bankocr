#include "bankocr/check_sum.h"
#include "bankocr/str_utils.h"

namespace {

int sum(const std::string& value) {
  auto num = 0;
  str_utils::foreach(value, [&value, &num](auto ch, auto i) {
    num += (ch - '0') * (value.size() - i);
  }); 
  return num;
}

int checksum(const std::string& value) {
  return sum(value) % 11;
}

}

bool check(const std::string& value) {
  return value.size() == 9 && checksum(value) == 0;
}
