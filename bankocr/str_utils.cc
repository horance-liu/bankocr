#include "bankocr/str_utils.h"

namespace str_utils {

std::string rtrim(const std::string& s, ssize_t from) {
  auto last = s.size();
  while (last != from && ::isspace(s[last - 1])) {
    --last;
  }
  return s.substr(0, last);
}

int diff(const std::string& lhs, const std::string& rhs) {
  auto num = 0;
  foreach(lhs, [&num, &lhs, &rhs](auto, auto i) {
    if (lhs[i] != rhs[i]) num++;
  });
  return num;
}

}
