#ifndef H616B6931_30DB_4BA3_861E_0A60F59A537E
#define H616B6931_30DB_4BA3_861E_0A60F59A537E

#include "bank_ocr/core/line_set.h"
#include <iostream>

struct AccountNumber {
  void parse(const LineSet&);
  std::string value() const;

private:
  void initialize(LineSet&);

private:
  Line merged;
};

std::istream& operator>>(std::istream&, AccountNumber&);
std::ostream& operator<<(std::ostream&, const AccountNumber&);

#endif
