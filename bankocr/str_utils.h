#ifndef H8F2AE8CC_0AEA_4204_BF33_DC6F3B710F21
#define H8F2AE8CC_0AEA_4204_BF33_DC6F3B710F21

#include <sstream>

namespace str_utils {

using string_size_t = std::string::size_type;

std::string rtrim(const std::string&, string_size_t = 0);
int diff(const std::string&, const std::string&);

template <typename F>
void foreach(const std::string& s, F f, int step = 1) {
  for (string_size_t i = 0; i != s.size(); i += step) {
    f(s[i], i);
  }
}

template <typename Iterator>
std::string join(Iterator begin, Iterator end, const char* sep) {
  std::stringstream ss;
  for (auto first = true; begin != end; ++begin) {
    ss << (first ? (first = false, "") : sep)
       << *begin;
  }
  return ss.str();
}

}

#endif
