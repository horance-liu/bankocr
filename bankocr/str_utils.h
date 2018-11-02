#ifndef H8F2AE8CC_0AEA_4204_BF33_DC6F3B710F21
#define H8F2AE8CC_0AEA_4204_BF33_DC6F3B710F21

#include <sstream>

namespace str_utils {

using ssize_t = std::string::size_type;

std::string rtrim(const std::string&, ssize_t from = 0);
int diff(const std::string&, const std::string&);

template <typename F>
void foreach(const std::string& s, F f, ssize_t step = 1) {
  for (ssize_t i = 0; i != s.size(); i += step) {
    f(s[i], i);
  }
}

template <typename Iterator>
std::string join(Iterator beg, Iterator end, const char* sep) {
  std::stringstream ss;
  for (auto first = true; beg != end; ++beg) {
    ss << (first ? (first = false, "") : sep) << *beg;
  }
  return ss.str();
}

}

#endif
