#ifndef CS235_FLASHCARD_H
#define CS235_FLASHCARD_H

#include <string>
#include <ostream>

using namespace std; // make std members visible

class Flashcard {
private:
	string front;	//the front of the card.
	string back;	//the back of the card.
public:
	Flashcard ();// constructor to create a flashcard.
	Flashcard (string strFront, string strBack);// constructor to create a flashcard.

	void setFront (string strVal);	//helper function to set the front of the flashcard.
	void setBack (string strVal);	//helper function to set the back of the flashcard.
	string getFront ();		//helper function to return the front of the flashcard.
	string getBack ();		//helper function to return the back of the flashcard.

	bool operator==(const Flashcard& rightCard); //operator == to compare two flashcards.
	ostream& operator << (const Flashcard& card);

	// extra credit
//	stringstream operator<<(const Flashcard& card);	//operator << to output the card to the stream.
};

//#include "Flashcard.cpp"
#endif
