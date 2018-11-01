#include "bankocr/account.h"
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

void exec(const char* file) {
  FileStream in(new std::ifstream(file), close);
  std::vector<Account> accounts {
      std::istream_iterator<Account>(*in),
      std::istream_iterator<Account>()
  };
  std::copy(accounts.cbegin(), accounts.cend(),
      std::ostream_iterator<Account>(std::cout, "\n")
  );
}

}

int main(int argc, char** argv) {
  try {
    exec(argv[1]);
  } catch (const std::invalid_argument& e) {
    std::cerr << "bad format: " << e.what() << std::endl;
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "unknown exception" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
