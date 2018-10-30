#include "bank_ocr/core/account_number.h"

void AccountNumber::parse(const LineSet& lines) {
  merged.reset();
  lines.merge(merged);
}

std::string AccountNumber::value() const {
  std::string result;
  merged.join(result);
  return result;
}

std::istream& operator>>(std::istream& is, AccountNumber& num) {
  std::string lines[4]; // last line is blank.
  for (auto& line : lines) {
    std::getline(is, line);
  }

  Lines set(lines, lines + 3);
  num.parse(set);
  return is;
}

std::ostream& operator<<(std::ostream& os, const AccountNumber& num) {
  os << num.value();
  return os;
}
