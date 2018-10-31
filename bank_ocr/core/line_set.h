#ifndef HF3C66EEC_6E29_47D3_AA31_0F08B2F8C4C0
#define HF3C66EEC_6E29_47D3_AA31_0F08B2F8C4C0

#include "bank_ocr/core/line.h"

struct LineSet {
  using Lines = std::deque<std::string>;

  LineSet(Lines& lines);

  bool isEmpty() const;
  void merge(Line&) const;

private:
  void save(const Lines& lines);

private:
  bool empty;
  std::deque<Line> lines;
};

#endif
