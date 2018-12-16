#ifndef __CS235_FLASHCARD_DECK_H_
#define __CS235_FLASHCARD_DECK_H_

#include <iostream>

#include "Flashcard.h"
#include "UniqueVector.h"

using namespace std;

class FlashcardDeck {

public:
  // If a card with the same front is not already in the pack, adds a new card with
  // the supplied front and back and returns true; otherwise, returns false.
  bool addCard(const string& front, const string& back) { return deck.insert( Flashcard{front, back}); }

  // If a card with the provided front is in the pack, removes the card from the
  // pack and returns true; otherwise, returns false.
  bool removeCard(const string& front) { return deck.remove( Flashcard{front} ); }

  // If a card with the provided front is in the pack, returns true; otherwise, returns false.
  bool containsCard(const string& front) { return deck.contains( Flashcard{front} ); }

  // Returns a string containing the Flashcards with each front followed by a
  // newline then its respective back followed by two newlines.
  string listFlashcards();


  // Any Flashcards in otherFlashcards that do not exist in this Flashcards are added to this.
  void combineFlashcards(FlashcardDeck& otherFlashcardDeck);

  // Combine the Flashcards in this with the Flashcards in otherFlashcards in such an order that
  // the first Flashcard in this is followed by the first Flashcard in otherFlashcardDeck
  // that does not exist in this, followed by the second Flashcard in this, then the second
  // Flashcard in otherFlashcardDeck that does not exist in this, etc, and add all remaining to the end.
  void shuffleFlashcards(FlashcardDeck& otherFlashcardDeck);


private:
  UniqueVector<Flashcard> deck;
};

#endif
