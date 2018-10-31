#include "bank_ocr/core/account_number.h"
#include "bank_ocr/core/check_sum.h"
#include <regex>
#include <set>
#include <stdexcept>

namespace {
  bool illegible(const std::string& s) {
    return s.find_first_of("?") != std::string::npos;
  }

  bool valid(const std::string& s) {
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
      if (valid(alt)) {
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
  line.alternatives(guess);
  return guess.get(value);
}

std::string AccountNumber::str() const {
  return valid(value) ? value : guess();
}

namespace {
  const std::regex re_line("^[ |_]+$");

  struct Validator {
    Validator(std::vector<std::string>& inputs)
      : inputs(inputs) {
     if (inputs.size() == 3 && !allEmpty()) {
       normalize();
       checkChars();
       checkLengths();
       checkSameSize();
       save();
     }
   }

  void merge(Line& merged) const {
    merged.reset();
    for (auto& line : lines) {
      merged.merge(line);
    }
  }

  private:
    static void assertTrue(bool expr, const char* msg) {
      if (!expr) throw std::invalid_argument(msg);
    }

    template <typename F>
    void foreach(F f) const {
      for (auto& in : inputs) {
        f(in);
      }
    }

    template <typename Pred>
    void allof(const char* msg, Pred pred) const {
      foreach([&pred, msg](auto& line) {
        assertTrue(pred(line), msg);
      });
    }

    void checkChars() const {
      allof("should contain [ |_]", [](auto& line) {
        return std::regex_match(line, re_line);
      });
    }

    void checkLengths() const {
      allof("length should be times of 3", [](auto& line) {
        return line.size() > 1 && line.size() % 3 == 0;
      });
    }

    void checkSameSize() const {
      std::set<std::string::size_type> lens;
      foreach([&lens](auto& line) {
        lens.insert(line.size());
      });
      assertTrue(lens.size() == 1, "length should be same");
    }

    void normalize() const {
      std::string::size_type max = 0;
      foreach([&max](auto& line) {
        if (max < line.size()) {
          max = line.size();
        }
      });

      foreach([&max](auto& line) {
        if (line.size() < max) {
          line += std::string(max - line.size(), ' ');
        }
      });
    }

    bool allEmpty() const {
      return std::all_of(inputs.begin(), inputs.end(), [](auto& line) {
        return line.empty();
      });
    }

    void save() {
      foreach([&](auto& line) {
        lines.emplace_back(line);
      });
    }

  private:
    std::vector<std::string>& inputs;
    std::vector<Line> lines;
  };
}

AccountNumber::AccountNumber(std::vector<std::string>& lines) {
  parse(lines);
}

void AccountNumber::parse(std::vector<std::string>& lines) {
  Validator validator(lines);
  validator.merge(line);
  value = line.value();
}

std::istream& operator>>(std::istream& is, AccountNumber& num) {
  std::vector<std::string> lines(4);
  for (auto& line : lines) {
    std::getline(is, line);
  }

  lines.pop_back();   // last line is blank.
  num.parse(lines);
  return is;
}

std::ostream& operator<<(std::ostream& os, const AccountNumber& num) {
  return os << num.str();
}
