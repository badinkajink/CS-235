//
// Created by WilliamUSER on 11/5/2017.
//

#ifndef JACKBLACK_ROUND_H
#define JACKBLACK_ROUND_H

#include <iostream>
#include <stack>
#include <vector>
#include "Card.h"
#include "Player.h"

class Round {
private:
    vector<Player*> *vPlayer;

    int total_num_winning_hands;
    int total_num_losing_hands;
    int total_hits;
    int total_num_cards_winning;
    int total_num_cards_losing;

    int total_num_numcard_winning;
    int total_num_wordcard_winning;
    int total_num_symbolcard_winning;
    string sWinningWords;

public:
    Round () {
        total_num_winning_hands=0;
        total_num_losing_hands=0;
        total_hits=0;
        total_num_cards_winning=0;
        total_num_cards_losing=0;

        total_num_numcard_winning=0;
        total_num_wordcard_winning=0;
        total_num_symbolcard_winning=0;
        sWinningWords="";
    }

    int getTotal_num_winning_hands() { return total_num_winning_hands;}
    int getTotal_num_losing_hands() { return total_num_losing_hands;}
    int getTotal_hits () { return total_hits;}
    int getTotal_num_cards_winning () { return total_num_cards_winning;}
    int getTotal_num_cards_losing () { return total_num_cards_losing;}

    int getTotal_num_numcard_winning () { return total_num_numcard_winning;}
    int getTotal_num_wordcard_winning () { return total_num_wordcard_winning;}
    int getTotal_num_symbolcard_winning () { return total_num_symbolcard_winning;}
    string getWinningWords () { return sWinningWords;}

    void setVPlayer (vector<Player*> *player) {vPlayer=player;}
    vector<Player*> *getVPlayer() { return vPlayer;}

    string PrintRoundStats(int iRound);

};

#endif //JACKBLACK_ROUND_H
