//
// Created by WilliamUSER on 11/6/2017.
//
#include <iomanip>
#include <fstream>
#include <iostream>

#include "Card.h"
#include "Player.h"
#include "Round.h"

string Round::PrintRoundStats(int iRound) {
    char type;
    Card *card;
    NumberCard *pnumcard;
    WordCard *pwordcard;
    SymbolCard *psymbolcard;
    int iWinningScore=0;
    int index=0;

    cout <<"Round "<<iRound<<"\n";
    for (int i=0; i<vPlayer->size(); i++) {
        cout << vPlayer->at(i)->getName() << ":";

        vector<Card *> vHand = vPlayer->at(i)->getHand();
        for (int j = 0; j < vHand.size(); j++) {
            card = vHand[j];

            type = card->getType();
            switch (type) {
                case 'N' : {
                    pnumcard = dynamic_cast<NumberCard *>(card);
                    cout << " " << pnumcard->getValue();
                    if (j == (vHand.size() - 1))
                        cout << ".";
                    else
                        cout << ",";
                }
                    break;
                case 'W' : {
                    pwordcard = dynamic_cast<WordCard *>(card);
                    cout << " " << pwordcard->getWord() << " (" << pwordcard->getValue() << ")";
                    if (j == (vHand.size() - 1))
                        cout << ".";
                    else
                        cout << ",";
                }
                    break;
                case 'S' : {
                    psymbolcard = dynamic_cast<SymbolCard *>(card);
                    cout << " " << psymbolcard->getSymbol() << " (" << psymbolcard->getLow() << "/"
                         << psymbolcard->getHigh() << " --> ";
                    if (vPlayer->at(i)->getIsSymbolLow()) {
                        cout << psymbolcard->getLow() << ")";
                    } else {
                        cout << psymbolcard->getHigh() << ")";
                    }
                    if (j == (vHand.size() - 1))
                        cout << ".";
                    else
                        cout << ",";
                }
                    break;
                default :
                    cout << "the type of card is invalid: " << type << "\n";
                    exit(0);
            }

        }

        int score = vPlayer->at(i)->getScore();
        cout << " TOTAL: " << score;
        if (score > 31) {
            cout << " (BUST).\n";
        } else {
            cout << ".\n";
        }

        if ((score <=31) && (score > iWinningScore)) {
            iWinningScore=score;
            index=i;
        }
    }

    bool isWinning=false;
    bool isTie=false;
    int iNumWinner=0;

    //determine if there is only one winner or a tie.
    for (int i=0; i<vPlayer->size(); i++) {
        int score = vPlayer->at(i)->getScore();
        if (score == iWinningScore){
            iNumWinner++;
        }
    }

    if (iNumWinner != 1) {
        // it is a tie.
        cout << "TIED:";

        // count the number of tie.
        int iNumTie=0;
        for (int i=0; i<vPlayer->size(); i++) {
            int score = vPlayer->at(i)->getScore();

            if (score == iWinningScore){
                cout <<" "<<vPlayer->at(i)->getName();
                vPlayer->at(i)->setIsTie(true);

                iNumTie++;

                // check for the last person who tie.
                if (iNumTie < iNumWinner) {
                    cout <<",";
                } else {
                    cout <<".";
                }
            }
        }
        cout << "\n\n";
    } else {
        // only one winner.
        cout << "WINNER: " << vPlayer->at(index)->getName() << ".\n\n";
        vPlayer->at(index)->setIsWinning(true);

        // update stats for winning hands.
        vector<Card *> vHand = vPlayer->at(index)->getHand();
        for (int k = 0; k < vHand.size(); k++) {
            card = vHand[k];
            type = card->getType();
            switch (type) {
                case 'N' :
                    total_num_numcard_winning++;
                    break;
                case 'W' :
                    total_num_wordcard_winning++;
                    pwordcard = dynamic_cast<WordCard *>(card);
                    sWinningWords += " " + pwordcard->getWord() + ",";
                    break;
                case 'S' :
                    total_num_symbolcard_winning++;
                    break;
            }
        }
    } // end of else for one winner.

    // update additional stats for the round
    for (int i=0; i<vPlayer->size(); i++) {
        //all the cards minus the card dealt at the start of the round.
        total_hits +=vPlayer->at(i)->getHand().size()-1;

        if (vPlayer->at(i)->getIsWinning()) {
            total_num_winning_hands++;
            total_num_cards_winning +=vPlayer->at(i)->getHand().size();

        } else if (!vPlayer->at(i)->getIsTie()){
            // it is a losing hand if not winning and not tie.
            total_num_losing_hands++;
            total_num_cards_losing +=vPlayer->at(i)->getHand().size();
        }
    }
}
