//
// Created by WilliamUSER on 11/5/2017.
//

#include <iomanip>
#include <fstream>
#include <iostream>
#include <stack>

#include "Card.h"
#include "Player.h"
#include "Round.h"

int readDeckFile(stack<Card*> &myDeck, string deckFile) {
    ifstream inFile;
    int count, number, low, high;
    char type='x', symbol;
    string word;

    //  cout << "The deckFile is: " << deckFile << "\n";
    inFile.open(deckFile);
    if (!inFile) {
        cout << "Unable to open file: " << deckFile;
        exit(1); // terminate with error
    }

    inFile >> count;
//    cout << "The total num of cards: " << count << "\n";
    for (int i = 0; i < count; i++) {
        inFile >> type;

        switch(type) {
            case 'N' : {
                inFile >> number;
//                cout << "  testing the number is: " << number << "\n";
                NumberCard* numcard = new NumberCard(type,number);
                myDeck.push((Card*)numcard);
            }
                break;
            case 'W' : {
                inFile >> word;
//                cout << "  testing the word is: " << word << "\n";
                WordCard* wordcard=new WordCard(type, word);
                wordcard->calcValueFromWord();
                myDeck.push((Card*)wordcard);
            }
                break;
            case 'S' : {
                inFile >> symbol;
                inFile >> low;
                inFile >> high;
//                cout << "  testing the symbol is: " << symbol << "; low: " << low << "; high: " << high << "\n";
                SymbolCard *symbolcard=new SymbolCard(type, symbol, low, high);
                myDeck.push((Card*)symbolcard);
            }
                break;
            default :
                cout << "the type of card is invalid: "<<type<<"\n";
                exit(0);
        }
    }
    inFile.close();
    return 0;
}

int PrintDeck(stack <Card*> &myDeck) {
    char type;
    Card *card;
    NumberCard *pnumcard;
    WordCard *pwordcard;
    SymbolCard *psymbolcard;

    cout << "PrintDeck function\n";

    while (!myDeck.empty())
    {
        card = myDeck.top();
        type = card->getType();
        switch(type) {
            case 'N' : {
//                pnumcard = (NumberCard*)card;
                pnumcard = dynamic_cast<NumberCard*>(card);
                cout << "  the number is: " << pnumcard->getValue() << "\n";
            }
                break;
            case 'W' : {
                pwordcard = dynamic_cast<WordCard*>(card);
                cout << "  the word is: " << pwordcard->getWord() << "\n";
            }
                break;
            case 'S' : {
                psymbolcard= dynamic_cast<SymbolCard*>(card);
                cout << "  the symbol is: " << psymbolcard->getSymbol() << "; low: " << psymbolcard->getLow() << "; high: " << psymbolcard->getHigh() << "\n";
            }
                break;
            default :
                cout << "the type of card is invalid: "<<type<<"\n";
                exit(0);
        }
        myDeck.pop();
    }

    cout << "exiting PrintDeck function\n";
    return 0;
}


int readPlayersFile(vector <Player*> &vPlayer, string playersFile) {
    ifstream inFile;
    int count, iMaxHit;
    string name;

//    cout << "The playerFile is: " << playersFile << "\n";
    inFile.open(playersFile);
    if (!inFile) {
        cout << "Unable to open file: " << playersFile;
        exit(1); // terminate with error
    }

    inFile >> count;
//    cout << "The total num of players: " << count << "\n";
    for (int i = 0; i < count; i++) {
        inFile >> name;
        inFile >> iMaxHit;
//        cout << "the name is: " << name << "; the max hit is: " << iMaxHit << "\n";
        Player* player = new Player(name,iMaxHit);
        vPlayer.push_back(player);
    }

    inFile.close();
    return 0;
}

int printPlayers(vector<Player*>vPlayer) {
    int size;
    Player *player;

//    cout<<"player vector size: "<<vPlayer.size()<<"\n";
    cout<<"Running simulation with players:\n";
    for (int i=0; i<vPlayer.size(); i++ ) {
        player=vPlayer.at(i);
        cout << player->getName() << " (Max Hit: " << player->getMaxHit() << ")\n";
    }
    cout <<"\n";
}

int PlayGame (stack <Card*> &myDeck, const vector <Player*> &vPlayer, vector <Round*> &vRound) {
    int	iRound=0;
    Card *card;

    while (!myDeck.empty()) {

        //allocate a vector, vTmpPlayer.
        vector<Player*> *vTmpPlayer=new vector<Player*>;

        //Copy each player in vPlayer to vTmpPlayer.
        //Each player in vTmpPlayer is dealt with one card at the start of each round.
        int i=0;
        while (i < vPlayer.size() && !myDeck.empty()) {
            string name = vPlayer.at(i)->getName();
            int maxHit = vPlayer.at(i)->getMaxHit();

            Player* player = new Player(name,maxHit);

            card = myDeck.top();

            player->deal(card);
            vTmpPlayer->push_back(player);

            myDeck.pop();
            i++;
        }

        //starting with the first player, each players decides whether to hit or not.
        i = 0;
        while (i < vTmpPlayer->size() && !myDeck.empty()) {
            //For a given player, keep hitting until false
            bool keepHitting=true;
            while (!myDeck.empty() && keepHitting) {
                card = myDeck.top();
                keepHitting=vTmpPlayer->at(i)->hit(card);
                if (keepHitting) {
                    //The card has been hit successfully, so need to pop it from the deck.
                    myDeck.pop();
                }
            }
            //go to the next player in the vector
            i++;
        }

        if (i == vPlayer.size() ) {
            // all players have hit, and this round finishes.
            Round* round = new Round();

            round->setVPlayer(vTmpPlayer);

            iRound ++;

            //need to update stats in round before push_back
            round->PrintRoundStats(iRound);

            vRound.push_back(round);
        }
    }
}

void PrintAnalytics (const vector <Player*> &vPlayer, const vector <Round*> &vRound) {
    int total_num_winning_hands=0;
    int total_num_losing_hands=0;
    int total_hits=0;
    int total_num_cards_winning=0;
    int total_num_cards_losing=0;

    int total_num_numcard_winning=0;
    int total_num_wordcard_winning=0;
    int total_num_symbolcard_winning=0;
    string sWinningWords="";

    for (int i=0; i<vRound.size(); i++){
        total_num_winning_hands += vRound[i]->getTotal_num_winning_hands();
        total_num_losing_hands += vRound[i]->getTotal_num_losing_hands();
        total_hits +=vRound[i]->getTotal_hits();
        total_num_cards_winning += vRound[i]->getTotal_num_cards_winning();
        total_num_cards_losing += vRound[i]->getTotal_num_cards_losing();

        total_num_numcard_winning += vRound[i]->getTotal_num_numcard_winning();
        total_num_wordcard_winning += vRound[i]->getTotal_num_wordcard_winning();
        total_num_symbolcard_winning += vRound[i]->getTotal_num_symbolcard_winning();
        sWinningWords += vRound[i]->getWinningWords();
    }

    cout <<"GAME ANALYSIS\n";
    cout <<"Average number of hits per player per round: "<<setprecision (3)<< (double)total_hits/(vRound.size()*vPlayer.size()) <<".\n";
    cout <<"Average number of cards in winning hands: "<< setprecision (3) << (double)total_num_cards_winning/total_num_winning_hands <<".\n";
    cout <<"Average number of cards in losing hands: "<< setprecision (3) << (double)total_num_cards_losing/total_num_losing_hands <<".\n\n";

    cout <<"Average number of number cards in winning hands: "<< setprecision (3) << (double)total_num_numcard_winning/total_num_winning_hands <<".\n";
    cout <<"Average number of word cards in winning hands: "<< setprecision (2) << (double)total_num_wordcard_winning/total_num_winning_hands <<".\n";
    cout <<"Average number of symbol cards in winning hands: "<< setprecision (2) << (double)total_num_symbolcard_winning/total_num_winning_hands <<".\n";

    int len=sWinningWords.length();
    sWinningWords[len-1]='.';
    cout <<"Words from winning hands:"<< sWinningWords <<"\n";
}


int main(int argc, char* argv[]) {
    string deckFile, playersFile;

    switch(argc) {
        case 1 :
            deckFile = "defaultDeck.data";
            playersFile = "defaultPlayers.data";
            cout << "No deck file provided. Using default deck file instead.\n";
            cout << "No players file provided. Using default players file instead.\n";
            break;
        case 2 :
            deckFile = argv[1];
            playersFile = "defaultPlayers.data";
            cout << "No players file provided. Using default players file instead.\n";
            break;
        case 3 :
            deckFile = argv[1];
            playersFile = argv[2];
            break;
        default :
            cout << "Usage is JackBlack ValidDeck.data ValidPlayers.data\n";
            exit(0);
    }

//    cout << "The deck file is: " << deckFile <<"; the players file is:" << playersFile <<"\n";
    stack<Card*> myDeck;
    readDeckFile(myDeck,deckFile);
//    myGame.PrintDeck(myDeck);

    vector<Player*> vPlayer;
    readPlayersFile(vPlayer,playersFile);
    printPlayers(vPlayer);

    vector<Round*> vRound;
    PlayGame(myDeck,vPlayer,vRound);
    PrintAnalytics(vPlayer,vRound);

//    std::cin.get();
    return 0;
}