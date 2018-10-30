#include "bank_ocr/core/illformed_number_error.h"

const char* IllformedNumberError::what() const noexcept {
  return "illformed number";
}
