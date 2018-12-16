#ifndef __CSCI235_FLASHCARD_CPP_
#define __CSCI235_FLASHCARD_CPP_

#include "Flashcard.h"

ostream& operator << (ostream& out, const Flashcard& c) {
  out << c.front << "\n" << c.back << "\n\n";
  return out;
}


#endif
