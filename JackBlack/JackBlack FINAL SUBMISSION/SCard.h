//
// Created by WilliamUSER on 11/5/2017.
//

#ifndef JACKBLACK_SCARD_H
#define JACKBLACK_SCARD_H

#include <iostream>
using namespace std; // make std members visible

class SCard {
private:
    char cType;
    int	iValue;
    string	sWord;
    char	cSymbol;
    int	iMin;
    int	iMax;
public:
    SCard(char type, int value, string word, char symbol, int min, int max) {
        cType=type;
        iValue=value;
        sWord=word;
        cSymbol=symbol;
        iMin = min;
        iMax = max;

//        cout << "Type: "<<cType<<"; Value: "<<iValue<<"; Word: "<<sWord<<"; Symbol: " << cSymbol << "; Min: " << iMin << "; Max: " << iMax << "\n";
    }
    void setType (char type)        {cType=type;}
    void setValue (int value)       {iValue = value;}
    void setWord (string word)      {sWord = word;}
    void setSymbol (char symbol)    {cSymbol = symbol;}
    void setMin(int min)            {iMin=min;}
    void setMax(int max)            {iMax=max;}

    char getType()                  {return cType;}
    int getValue()                  {return iValue;}
    string	getWord()               {return sWord;}
    char getSymbol()                {return cSymbol;}
    int getMin()                    {return iMin;}
    int getMax()                    {return iMax;}

    int calcValueFromWord ();
};

#endif //JACKBLACK_SCARD_H
