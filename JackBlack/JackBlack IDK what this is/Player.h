//
// Created by WilliamUSER on 11/5/2017.
//

#ifndef JACKBLACK_PLAYER_H
#define JACKBLACK_PLAYER_H

#include <iostream>
#include <stack>
#include <vector>

#include "Card.h"

class Player {
private:
    string	sName;
    int	iMaxHit;
    vector <Card*> vHand;

    int	iScore;
    bool isSymbolLow;
    bool isWinning;
    bool isTie;

public:
    Player (string name, int maxHit) {
        sName=name;
        iMaxHit=maxHit;

        iScore=0;
        isSymbolLow=false;
        isWinning=false;
        isTie=false;
    }
    string getName() {return sName;}
    int getMaxHit () {return iMaxHit;}

    int getScore() {return iScore;}
    bool getIsSymbolLow() {return isSymbolLow;}
    bool getIsWinning() {return isWinning;}
    bool getIsTie () { return isTie;}

    vector <Card*> getHand() { return vHand;}

    void setName(string name) {sName=name;}
    void setIsWinning (bool winning) {isWinning=winning;}
    void setIsTie (bool tie) {isTie=tie;}

    bool deal(Card* card); // add one card to a player
    bool hit(Card* card); // to decide if we shall keep hitting another card. if yes, add this card to the vHand, and return true to hit another card.
};

#endif //JACKBLACK_PLAYER_H
