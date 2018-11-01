#include "bankocr/str_utils.h"

namespace str_utils {
  std::string rtrim(const std::string& s, std::string::size_type from) {
    auto last = s.size() - 1;
    while (last != from && ::isspace(s[last])) {
      --last;
    }
    return s.substr(0, last + 1);
  }

  int diff(const std::string& lhs, const std::string& rhs) {
    auto num = 0;
    for (std::string::size_type i = 0; i != lhs.size(); ++i) {
      if (lhs[i] != rhs[i]) num++;
    }
    return num;
  }
}
