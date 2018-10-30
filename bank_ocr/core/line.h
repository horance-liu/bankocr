#ifndef HFC416880_5F5C_463A_B0D0_48027742AA56
#define HFC416880_5F5C_463A_B0D0_48027742AA56

#include <deque>
#include <string>

struct Alternative {
  virtual void accept(const std::string&) = 0;
  virtual ~Alternative() {}
};

struct Line {
  Line();
  Line(const std::string& line);

  void reset();
  void merge(const Line& rhs);

  std::string value() const;
  void alternatives(Alternative&) const;

private:
  std::deque<std::string> nums;
};

#endif
