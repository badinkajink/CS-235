//
// Created by WilliamUSER on 11/6/2017.
//

#include <iomanip>
#include <fstream>
#include <iostream>

#include "Card.h"
#include "Player.h"

// add one card to a player.
bool Player::deal(Card* card) {
    vHand.push_back(card);
}

// to decide if we shall keep hitting another card. if yes, add this card to the vHand, and return true to hit another card.
bool Player::hit(Card *card) {
    char type;
    SymbolCard *psymbolcard;
    int totalValue=0, totalLow=0, totalHigh=0;

    // traverse through the cards in the hand to determine the maximum value.
    for (int i=0; i<vHand.size(); i++) {
        type = vHand[i]->getType();
        if (type != 'S') {
            totalValue += vHand[i]->getValue();
        } else {
            psymbolcard = dynamic_cast<SymbolCard *>(vHand[i]);
            totalLow += psymbolcard->getLow();
            totalHigh += psymbolcard->getHigh();
        }
    }

    bool keepHitting= false;
    if ((totalValue+totalHigh) <= iMaxHit) {
        // keep hitting since the total score is less than MaxHit
        keepHitting=true;
        iScore = totalValue + totalHigh;
        isSymbolLow=false;

    } else if (totalValue + totalHigh <=31) {
        // no more hitting since the total score is more than MaxHit, but less than 31.
        keepHitting=false;
        iScore = totalValue + totalHigh;
        isSymbolLow=false;

    } else if ((totalValue+totalLow) <= iMaxHit) {
        // the high values busted, so let us try the low values. The total socre is less than Max, so keep hitting.
        keepHitting=true;
        iScore = totalValue + totalLow;
        isSymbolLow=true;

    } else {
        // no more hitting since the total score of low values is either more than MaxHit or busted.
        keepHitting=false;
        iScore = totalValue + totalLow;
        isSymbolLow=true;
    }

    if (keepHitting)
        vHand.push_back(card);

    return keepHitting;
}