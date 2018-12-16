//
// Created by WilliamUSER on 11/5/2017.
//

#ifndef JACKBLACK_TCARD_H
#define JACKBLACK_TCARD_H

#include <iostream>

using namespace std; // make std members visible


class TCard {
private:
    string front;	//the front of the card.
    string back;	//the back of the card.
public:
    TCard () {};// constructor to create a flashcard.
    // constructor to create a flashcard.
    TCard (string strFront, string strBack) : front(strFront), back(strBack) {}
    void setFront (string strVal) {front = strVal;}	//helper function to set the front of the flashcard.
    void setBack (string strVal) {back = strVal;}	//helper function to set the back of the flashcard.
    string getFront () {return front;} // function to return the front of the flashcard.
    string getBack () {return back;}		//helper function to return the back of the flashcard.

    //operator == to compare two flashcards.
    bool operator == (const TCard& c1) { return (c1.front == front); }

    ostream& operator << (const TCard& card);
//    friend ostream& operator << (ostream& out, const Card& card);

};

#endif //JACKBLACK_TCARD_H
