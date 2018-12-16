//
// Created by WilliamUSER on 11/5/2017.
//

#include "TCard.h"


ostream& operator << (ostream& out, const TCard& card) {
    TCard c=card;

    out << c.getFront() << "\n" << c.getBack() << "\n\n";
//    out << c.front << "\n" << c.back << "\n\n";
    return out;
}

/*
int main(int argc, char* argv[]) {
    string str;

    TCard card1 = {"testing","back"};
    TCard card2 ("testing2","back2");

    cout << "card1 front: " << card1.getFront() << " card1 back: " << card1.getBack() << ".\n";
    cout << card1;
    cout << card2;

    std::cout << "Hello, World!" << std::endl;


    return 0;
}
*/