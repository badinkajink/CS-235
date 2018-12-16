#ifndef CS235_FLASHCARD_DECK_CPP
#define CS235_FLASHCARD_DECK_CPP

#include <iostream>
#include <string>
#include <stdexcept>

#include "UniqueVector.h"
#include "Flashcard.h"
#include "FlashcardDeck.h"

using namespace std;    // make std members visible


//add the card to the deck if a card with the same front value doesn't exist.
bool FlashcardDeck::addCard(const string& front, const string& back)
{
	Flashcard tmpCard;

	tmpCard.setFront(front);
	tmpCard.setBack(back);

	if (vDeck.insert(tmpCard)) {
		cout << "insert tmpCard successful.\n";
		return true;
	} else {
		cout << "insert tmpCard fail.\n";
		return false;
	}
}

//remove the card from the deck.
bool FlashcardDeck::removeCard (const string& front)
{
	Flashcard tmpCard;

	tmpCard.setFront(front);
	tmpCard.setBack("NA");

	if (vDeck.remove(tmpCard)) {
		cout << "remove tmpCard successful.\n";
		return true;
	} else {
		cout << "remove tmpCard fail.\n";
		return false;
	}
}

//check if a card exists in the deck.
bool FlashcardDeck::containsCard (const string& front)
{
	Flashcard tmpCard;

	tmpCard.setFront(front);
	tmpCard.setBack("NA");

	if (vDeck.contains(tmpCard)) {
		cout << "containsCard tmpCard successful.\n";
		return true;
	} else {
		cout << "containsCard tmpCard fail.\n";
		return false;
	}
}

//Return a string containing all of the flashcards.
string FlashcardDeck::listFlashcards ()
{
	string strDeck="";

	if (vDeck.size() == 0)
		return strDeck;

	for (unsigned int i=0; i < vDeck.size(); i++){
		strDeck.append(vDeck[i].getFront());
		strDeck.append("\n"); 
		strDeck.append(vDeck[i].getBack());
		strDeck.append("\n\n"); 
	}	
	
	return strDeck;
}

//add unique cards in otherFlashcardDeck to the existing deck.
void FlashcardDeck::combineFlashcards(FlashcardDeck& otherFlashcardDeck)
{
}

//shuffle the cards from both decks.
void FlashcardDeck::shuffleFlashcards(FlashcardDeck& otherFlashcardDeck)
{
}

/*
int main ()
{
        FlashcardDeck deck;

	deck.addCard("Captain America","Chris Evans");
	deck.addCard("Iron Man","RDJ");
	deck.addCard("Black Widow","ScarJo");
	deck.removeCard("Ant Man");
	deck.containsCard("Iron Man");
	deck.removeCard("Iron Man");

	string strDeck = deck.listFlashcards();
	cout << "The list of Flashcards is: \n" << strDeck;

}
*/
#endif
