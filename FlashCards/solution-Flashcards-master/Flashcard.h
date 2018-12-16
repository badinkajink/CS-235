#ifndef __CSCI235_FLASHCARD_H_
#define __CSCI235_FLASHCARD_H_

#include <iostream>

using namespace std;

struct Flashcard {
  string front;
  string back;
  bool operator == (const Flashcard& c1) { return (c1.front == front); }
  friend ostream& operator << (ostream& out, const Flashcard& c);
};


#endif
