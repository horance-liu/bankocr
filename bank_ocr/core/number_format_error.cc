#include "bank_ocr/core/number_format_error.h"

NumberFormatError::NumberFormatError(const char* msg)
  : msg(msg) {
}

const char* NumberFormatError::what() const noexcept {
  return msg;
}
