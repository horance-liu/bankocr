#ifndef HF3C66EEC_6E29_47D3_AA31_0F08B2F8C4C0
#define HF3C66EEC_6E29_47D3_AA31_0F08B2F8C4C0

#include "bank_ocr/core/line.h"

using Lines = std::vector<std::string>;

struct LineSet {
  LineSet(Lines& lines);

  void merge(Line&) const;

private:
  void initialize(Lines& lines);

private:
  std::vector<Line> lines;
};

#endif
