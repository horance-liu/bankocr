#include "bankocr/account.h"
#include "bankocr/check_sum.h"

#include <regex>
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
        return value + " AMB " + list();
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
    std::string list() const {
      std::string result("[");
      bool first = true;
      for (auto& alt : alts) {
        result += (first ? "" : ", ");
        result += alt;
        first = false;
      }
      return result += "]";
    }

  private:
    std::vector<std::string> alts;
  };

  std::string guess(const Line& line, const std::string& value) {
    Guess guess;
    line.alternatives(guess);
    return guess.get(value);
  }
}

std::string Account::str() const {
  return valid(value) ? value : guess(line, value);
}

namespace {
  struct Validator {
    Validator(Account::Lines& inputs) : inputs(inputs) {
      normalize();
      checkLengths();
      checkChars();
      save();
   }

  void merge(Line& merged) const {
    merged.reset();
    for (auto& line : lines) {
      merged.merge(line);
    }
  }

  private:
    static std::string rtrim(const std::string& s) {
      auto last = s.size() - 1;
      while (last != MAX_LENGTH - 1 && ::isspace(s[last])) {
        --last;
      }
      return s.substr(0, last + 1);
    }

    static std::string suffix(const std::string& s) {
      return std::string(MAX_LENGTH - s.size(), ' ');
    }

    static void normalize(std::string& line) {
      if (line.size() < MAX_LENGTH) {
        line += suffix(line);
      } else if (line.size() > MAX_LENGTH) {
        line = rtrim(line);
      }
    }

    void normalize() {
      for (auto& line : inputs) {
        normalize(line);
      }
    }

    static void assertTrue(const char* msg, bool expr) {
      if (!expr) throw std::invalid_argument(msg);
    }

    template <typename Pred>
    bool allof(Pred pred) const {
      return std::all_of(inputs.begin(), inputs.end(), [&pred](auto& line) {
        return pred(line);
      });
    }

    void checkChars() const {
      static const std::regex re("^[ |_]+$");
      assertTrue("should contain [ |_]", allof([](auto& line) {
        return std::regex_match(line, re);
      }));
    }

    enum {
      MAX_LINE = 3, MAX_LENGTH = 27,
    };

    void checkLengths() const {
      assertTrue("should be 3 lines", inputs.size() == MAX_LINE);
      assertTrue("length should be 27", allof([](auto& line) {
        return line.size() == MAX_LENGTH;
      }));
    }

    void save() {
      for (auto& line : inputs) {
        lines.emplace_back(line);
      };
    }

  private:
    Account::Lines& inputs;
    std::vector<Line> lines;
  };
}

void Account::parse(Lines& lines) {
  Validator validator(lines);
  validator.merge(line);
  value = line.value();
}

Account::Account(Lines& lines) {
  parse(lines);
}

std::istream& operator>>(std::istream& is, Account& num) {
  Account::Lines lines(4);
  for (auto& line : lines) {
    std::getline(is, line);
  }

  lines.pop_back();  // last line is blank.
  num.parse(lines);
  return is;
}

std::ostream& operator<<(std::ostream& os, const Account& num) {
  return os << num.str();
}
