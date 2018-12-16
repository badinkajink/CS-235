#ifndef __CSCI235_FLASHCARD_DECK_CPP_
#define __CSCI235_FLASHCARD_DECK_CPP_

#include "FlashcardDeck.h"

string FlashcardDeck::listFlashcards() {
  if (deck.empty()) {
    return "";
  }

  string listOfCards = "";
  Flashcard currentCard;

  for (unsigned int i = 0; i < deck.size(); i++) {
    deck.at(i, currentCard);
    listOfCards = listOfCards + currentCard.front + "\n" + currentCard.back +"\n\n";
  }

  return listOfCards;

}


void FlashcardDeck::combineFlashcards(FlashcardDeck& otherFlashcardDeck) {

  Flashcard currentCard;

  for (unsigned int i = 0; i < otherFlashcardDeck.deck.size(); i++) {
    otherFlashcardDeck.deck.at(i, currentCard);
    addCard(currentCard.front, currentCard.back);
  }

}


void FlashcardDeck::shuffleFlashcards(FlashcardDeck& otherFlashcardDeck) {

  UniqueVector<Flashcard> tempDeck;
  Flashcard currentCard;
  unsigned int i = 0;
  unsigned int j = 0;

  while (i < deck.size()) {

    // insert one card from this deck
    deck.at(i, currentCard);
    tempDeck.insert(currentCard);
    i++;

    // insert the first card from other deck that is not in this deck

    // if j is valid position (AKA still searching through other deck)
    if (otherFlashcardDeck.deck.at(j, currentCard)) {
      // find the first card from other deck that is not in this deck
      // or j extends over size of other deck
      while (deck.contains(currentCard) && j < otherFlashcardDeck.deck.size()) {
	j++;
	otherFlashcardDeck.deck.at(j, currentCard);
      }
      // if j did not extend over size of other deck
      // THAT IS, a valid card was found; insert
      if (j < otherFlashcardDeck.deck.size()) {
	tempDeck.insert(currentCard);
	j++;
      }
    }
  }

  // add remaining cards from the other deck
  while (j < otherFlashcardDeck.deck.size()) {
    otherFlashcardDeck.deck.at(j, currentCard);
    tempDeck.insert(currentCard);
    j++;
  }

  // transfer cards from temp deck to this deck
  deck.clear();
  for (unsigned int k = 0; k < tempDeck.size(); k++) {
    tempDeck.at(k, currentCard);
    deck.insert(currentCard);
  }

}


#endif
