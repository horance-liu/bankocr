#ifndef H616B6931_30DB_4BA3_861E_0A60F59A537E
#define H616B6931_30DB_4BA3_861E_0A60F59A537E

#include "bank_ocr/core/line.h"
#include <iostream>
#include <vector>

struct LineSet;

struct AccountNumber {
  AccountNumber() = default;
  AccountNumber(std::vector<std::string>&);

  void parse(std::vector<std::string>& lines);
  std::string str() const;

private:
  std::string guess() const;

private:
  Line line;
  std::string value;
};

std::istream& operator>>(std::istream&, AccountNumber&);
std::ostream& operator<<(std::ostream&, const AccountNumber&);

#endif
