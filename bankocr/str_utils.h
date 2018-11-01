#ifndef H8F2AE8CC_0AEA_4204_BF33_DC6F3B710F21
#define H8F2AE8CC_0AEA_4204_BF33_DC6F3B710F21

#include <string>

namespace str_utils {

std::string rtrim(const std::string&, std::string::size_type = 0);
int diff(const std::string&, const std::string&);

template <typename Iterator>
std::string join(Iterator begin, Iterator end, const char* sep) {
  std::string result;
  for (auto first = true; begin != end; ++begin) {
    result += (first ? "" : sep);
    result += *begin;
    first = false;
  }
  return result;
}

}

#endif
