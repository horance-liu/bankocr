#ifndef H18DAD269_6DDC_436A_8E4E_9BC0D428E66A
#define H18DAD269_6DDC_436A_8E4E_9BC0D428E66A

#include <exception>
#include <string>

struct IllformedNumberError : std::exception {
  IllformedNumberError(const std::string& msg);
  const char* what() const noexcept;

private:
  std::string msg;
};

#endif
