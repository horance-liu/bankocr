#ifndef H8F2AE8CC_0AEA_4204_BF33_DC6F3B710F21
#define H8F2AE8CC_0AEA_4204_BF33_DC6F3B710F21

#include <sstream>

namespace str_utils {

std::string rtrim(const std::string&, std::string::size_type = 0);
int diff(const std::string&, const std::string&);

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
