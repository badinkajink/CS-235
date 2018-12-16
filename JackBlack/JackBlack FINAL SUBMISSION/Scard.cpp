//
// Created by WilliamUSER on 11/5/2017.
//
#include <iomanip>
#include <fstream>
#include <iostream>
#include <stack>

#include "SCard.h"


int calcValueFromWord () {
    return 10;
}


int readDeckFile(stack<SCard*> & mystack, string deckFile) {
    ifstream inFile;

    int count, value, min, max;
    char type='x', symbol;
    string word;

    string defaultWord="none";
    char defaultSymbol=' ';
    int defaultValue=0;
    int defaultMin=0;
    int defaultMax=1;

    cout << "The deckFile is: " << deckFile << "\n";
    inFile.open(deckFile);
    if (!inFile) {
        cout << "Unable to open file: " << deckFile;
        exit(1); // terminate with error
    }

    inFile >> count;
    cout << "The total num of cards: " << count << "\n";

    for (int i = 0; i < count; i++) {
        inFile >> type;

        switch(type) {
            case 'N' : {
                inFile >> value;
                cout << "  the number is: " << value << "\n";
//                Card(char type, int value, string word, char symbol, int min, int max)
                SCard* numcard = new SCard(type, value, defaultWord, defaultSymbol, defaultMin, defaultMax);
                mystack.push(numcard);
                }
                break;
            case 'W' : {
                inFile >> word;
                cout << "  the word is: " << word << "\n";
//                Card(char type, int value, string word, char symbol, int min, int max)
                SCard* wordcard=new SCard(type, defaultValue, word, defaultSymbol, defaultMin, defaultMax);
                mystack.push(wordcard);
                }
                break;
            case 'S' : {
                inFile >> symbol;
                inFile >> min;
                inFile >> max;
                cout << "  the symbol is: " << symbol << "; min: " << min << "; max: " << max << "\n";
//                Card(char type, int value, string word, char symbol, int min, int max)
                SCard *symbolcard=new SCard(type, defaultValue, defaultWord, symbol, min, max);
                mystack.push(symbolcard);
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

int PrintDeck(stack <SCard*> &mystack) {
    char type;
    SCard *card;

    cout << "In PrintDeck function\n";

    while (!mystack.empty())
    {
        card = mystack.top();
        type = card->getType();

        switch(type) {
            case 'N' : {
                cout << "  the number is: " << card->getValue() << "\n";
            }
                break;
            case 'W' : {
                cout << "  the word is: " << card->getWord() << "\n";
            }
                break;
            case 'S' : {
                cout << "  the symbol is: " << card->getSymbol() << "; min: " << card->getMin() << "; max: " << card->getMax() << "\n";
            }
                break;
            default :
                cout << "the type of card is invalid: "<<type<<"\n";
                exit(0);
        }
        mystack.pop();
    }

    cout << "exiting PrintDeck function\n";
    return 0;
}

/*
class Player {
    string sName;
    int iMaxHit;
}
*/

int readPlayersFile(string playersFile) {
    ifstream inFile;
    int count, iMaxHit;
    string name;

    cout << "The playersFile is: " << playersFile << "\n";
    inFile.open(playersFile);
    if (!inFile) {
        cout << "Unable to open file: " << playersFile;
        exit(1); // terminate with error
    }

    inFile >> count;
    cout << "The total num of players: " << count << "\n";
    for (int i = 0; i < count; i++) {
        inFile >> name;
        inFile >> iMaxHit;
        cout << "the name is: " << name << "; the max hit is: " << iMaxHit << "\n";
    }

    inFile.close();
    return 0;
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

    cout << "The deck file is: " << deckFile <<"; the players file is:" << playersFile <<"\n";
    readPlayersFile(playersFile);

    stack<SCard*> mystack;
    readDeckFile(mystack,deckFile);
    PrintDeck(mystack);

//  cin.get();
    return 0;
}
