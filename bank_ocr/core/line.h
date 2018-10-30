#ifndef HFC416880_5F5C_463A_B0D0_48027742AA56
#define HFC416880_5F5C_463A_B0D0_48027742AA56

#include <vector>
#include <string>

struct Line {
  Line() = default;
  Line(const std::string& line);

  void reset();
  void merge(const Line& rhs);
  void join(std::string& result) const;

private:
  std::vector<std::string> nums;
};

#endif
