#include "bank_ocr/core/account_number.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <memory>

namespace {
  auto close = [](std::ifstream* s) {
    s->close();
  };

  using FileStream = std::unique_ptr<std::ifstream, decltype(close)>;
}

int main(int argc, char** argv) {
  std::vector<AccountNumber> accounts;

  FileStream in(new std::ifstream(argv[1]), close);
  std::copy(std::istream_iterator<AccountNumber>(*in),
            std::istream_iterator<AccountNumber>(),
            std::back_inserter(accounts));

  std::copy(accounts.begin(), accounts.end(),
            std::ostream_iterator<AccountNumber>(std::cout, "\n"));

  return 0;
}
