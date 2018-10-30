#include "bank_ocr/core/account_number.h"
#include "bank_ocr/core/check_sum.h"

void AccountNumber::parse(const LineSet& lines) {
  merged.reset();
  lines.merge(merged);
  value = merged.value();
}

namespace {
  bool illegible(const std::string& s) {
    return s.find_first_of("?") != std::string::npos;
  }

  bool isValid(const std::string& s) {
    return !illegible(s) && check(s);
  }

  struct Guess : Alternative {
    std::string get(const std::string& value) const {
      if (alts.size() == 1) {
        return alts.front();
      } else if(alts.size() > 1) {
        return value + " AMB " + amb();
      } else if(illegible(value)) {
        return value + " ILL";
      } else {
        return value + " ERR";
      }
    }

  private:
    void accept(const std::string& alt) override {
      if (isValid(alt)) {
        alts.emplace_back(alt);
      }
    }

  private:
    std::string amb() const {
      std::string result("[");
      bool first = true;
      for (auto& alt : alts) {
        result += (first ? "" : ", ");
        result += alt;
        first = false;
      }
      return result + "]";
    }

  private:
    std::deque<std::string> alts;
  };
}

std::string AccountNumber::guess() const {
  Guess guess;
  merged.alternatives(guess);
  return guess.get(value);
}

std::string AccountNumber::str() const {
  return valid() ? value : guess();
}

bool AccountNumber::valid() const {
  return isValid(value);
}

std::istream& operator>>(std::istream& is, AccountNumber& num) {
  std::string lines[4];
  for (auto& line : lines) {
    std::getline(is, line);
  }

  LineSet::Lines set(lines, lines + 3); // last line is blank.
  num.parse({set});
  return is;
}

std::ostream& operator<<(std::ostream& os, const AccountNumber& num) {
  os << num.str();
  return os;
}
