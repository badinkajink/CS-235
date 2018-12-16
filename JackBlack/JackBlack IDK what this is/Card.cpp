//
// Created by WilliamUSER on 11/1/2017.
//

#include <iomanip>
#include <fstream>
#include <iostream>

#include "Card.h"

int WordCard::calcValueFromWord()  {
    string tmpStr = sWord;
    string sVowel = "AEIOUaeiou";
    int tmpValue=0;

    for (int i=0; i<tmpStr.length(); i++) {
        size_t found = sVowel.find(tmpStr[i]);
        if (found!=string::npos) {
            tmpValue +=2;
        } else {
            tmpValue +=1;
        }
    }

    iValue = tmpValue % 16 + 1;
//    cout <<"the word: "<< tmpStr <<" has the value: "<< iValue <<"\n";
    return iValue;
}
