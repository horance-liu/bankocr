#ifndef H616B6931_30DB_4BA3_861E_0A60F59A537E
#define H616B6931_30DB_4BA3_861E_0A60F59A537E

#include "bank_ocr/core/line_set.h"
#include <iostream>

struct AccountNumber {
  void parse(const LineSet&);

  std::string str() const;
  bool valid() const;

private:
  void initialize(LineSet&);
  std::string guess() const;

private:
  Line merged;
  std::string value;
};

std::istream& operator>>(std::istream&, AccountNumber&);
std::ostream& operator<<(std::ostream&, const AccountNumber&);

#endif
