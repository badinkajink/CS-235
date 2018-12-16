//
// Created by WilliamUSER on 12/9/2017.
//

#ifndef STACKOVERDUE_BOOKFILEREADER_H
#define STACKOVERDUE_BOOKFILEREADER_H


#include <iomanip>
#include <fstream>
#include <iostream>

//unordered_map
#include <bits/stdc++.h>
#include <unordered_map>

#include "Book.h"

using namespace std;


//Reads books file and passes data to data structures contained in Library.
class BookFileReader {
public:
    bool readBookFile(unordered_map<int, Book*> &pumapBook, string sBookFileName);
    int printBookFile(unordered_map<int, Book*> &umapBook);
};



#endif //STACKOVERDUE_BOOKFILEREADER_H
