#include "bank_ocr/core/illformed_number_error.h"

IllformedNumberError::IllformedNumberError(const std::string& msg)
  : msg(msg) {
}

const char* IllformedNumberError::what() const noexcept {
  return msg.c_str();;
}
