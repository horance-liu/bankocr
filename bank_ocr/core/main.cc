#include "bank_ocr/core/account_number.h"
#include <fstream>
#include <iterator>
#include <algorithm>

int main(int argc, char** argv) {
  std::vector<AccountNumber> accounts;

  std::ifstream in(argv[1]);
  std::copy(std::istream_iterator<AccountNumber>(in),
            std::istream_iterator<AccountNumber>(),
            std::back_inserter(accounts));

  std::copy(accounts.begin(), accounts.end(),
            std::ostream_iterator<AccountNumber>(std::cout, "\n"));

  return 0;
}
