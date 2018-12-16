#ifndef CS235_FLASHCARD_CPP
#define CS235_FLASHCARD_CPP

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "Flashcard.h"

using namespace std;    // make std members visible

// constructor to create a flashcard.
Flashcard::Flashcard()
{
	string str1;
	// no operations.
}

// constructor to create a flashcard.
Flashcard::Flashcard(string strFront, string strBack)
{
	front = strFront;
	back = strBack;
}

//helper function to set the front of the flashcard.
void Flashcard::setFront(string strVal) 
{
	front = strVal;
}

//helper function to set the back of the flashcard.
void Flashcard::setBack(string strVal) 
{
	back = strVal;
}

//helper function to return the front of the flashcard.
string Flashcard::getFront() 
{
	return front;
}

//helper function to return the back of the flashcard.
string Flashcard::getBack() 
{
	return back;
}

//operator == to compare two flashcards.
bool Flashcard::operator==(const Flashcard& rightCard)
{
	// won't be able to call function "getFront" if the rightCard is of const modifier.
	Flashcard tmpCard = rightCard;

	cout << "Left hand front is: " << front << "; Right hand front is: " << tmpCard.getFront() << ".\n";	
	if (front.compare(tmpCard.getFront()) == 0) {
		cout << "both flashcards have the same front.\n";
		return true;
	} else {
		return false;
	} 
}

/*
int main ()
{
        Flashcard card1;
        Flashcard card2;

	card1.setFront("Dennis");
	card1.setBack("Xie");

	card2.setFront("Eileen");
	card2.setBack("Zhao");

	if (card1 == card2) 
		cout << "card1 front: " << card1.getFront() << " is equal to card2 front: " << card2.getFront() << ".\n";	
	else
		cout << "card1 front: " << card1.getFront() << " is not equal to card2 front: " << card2.getFront() << ".\n";	

	card2.setFront("Dennis");
	if (card1 == card2) 
		cout << "card1 front: " << card2.getFront() << " is equal to card2 front: " << card2.getFront() << ".\n";	
	else
		cout << "card1 front: " << card2.getFront() << " is not equal to card2 front: " << card2.getFront() << ".\n";	


        Flashcard card3 = {"testing","back"};
	cout << "card3 front: " << card3.getFront() << " card3 back: " << card3.getBack() << ".\n";	
}
*/

#endif
