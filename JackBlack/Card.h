//
// Created by WilliamUSER on 11/1/2017.
//

#ifndef JACKBLACK_CARD_H
#define JACKBLACK_CARD_H

#include <iostream>

using namespace std; // make std members visible

enum CardType {NUMBER, WORD, SYMBOL};

class Card {
protected:
    char cType;
    int iValue;
public:
    virtual ~Card () {}
    void setType (char);
    void setValue (int);
    char getType() {return cType;}
    int getValue() {return iValue;}
};

class NumberCard: public Card {
public:
    NumberCard(char type, int value) {
        cType=type;
        iValue=value;
    }
};

class WordCard: public Card {
    string sWord;
public:
    WordCard(char type, string word) {
        cType=type;
        sWord = word;

        iValue = 0; // will be updated via calling calcValueFromWord while the deck is read.
    }
    string getWord() {return sWord;}

    // calcValue from the word.
    int calcValueFromWord ();
};

class SymbolCard: public Card {
    char cSymbol;
    int iLow, iHigh;
public:
    SymbolCard(char type, char symbol, int low, int high) {
        cType=type;
        cSymbol=symbol;
        iLow = low;
        iHigh = high;

        iValue = 0; // need to decide in the run time.
    }
    char getSymbol() {return cSymbol;}
    int getLow() {return iLow;}
    int getHigh() {return iHigh;}
};

#endif //JACKBLACK_CARD_H
