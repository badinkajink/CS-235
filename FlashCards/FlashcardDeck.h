#ifndef CS235_FLASHCARD_DECK_H
#define CS235_FLASHCARD_DECK_H

#include <string>
#include "UniqueVector.h"
#include "Flashcard.h"


using namespace std; // make std members visible

class FlashcardDeck {
private:
	UniqueVector<Flashcard> vDeck;		//UniqueVector is used to hold a deck of flashcards.

public:
	bool addCard (const string& front, const string& back);	//add the card to the deck if a card with the same front value doesn't exist.
	bool removeCard (const string& front);			//remove the card from the deck.
	bool containsCard (const string& front);		//check if a card exists in the deck.

	string listFlashcards ();				//Return a string containing all of the flashcards.

	// extra credit
	void combineFlashcards(FlashcardDeck& otherFlashcardDeck);	//add unique cards in otherFlashcardDeck to the existing deck.
	void shuffleFlashcards(FlashcardDeck& otherFlashcardDeck);	//shuffle the cards from both decks.
};

//#include "FlashcardDeck.cpp"
#endif
