#ifndef H616B6931_30DB_4BA3_861E_0A60F59A537E
#define H616B6931_30DB_4BA3_861E_0A60F59A537E

#include "bankocr/line.h"
#include <iostream>
#include <vector>

struct Account {
  using Lines = std::vector<std::string>;

  Account() = default;
  Account(Lines&);

  void parse(Lines& lines);
  std::string str() const;

private:
  Line line;
  std::string value;
};

std::istream& operator>>(std::istream&, Account&);
std::ostream& operator<<(std::ostream&, const Account&);

#endif
