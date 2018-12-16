//
// Created by WilliamUSER on 12/9/2017.
//

#ifndef STACKOVERDUE_ACCOUNTFILEREADER_H
#define STACKOVERDUE_ACCOUNTFILEREADER_H

#include <iomanip>
#include <fstream>
#include <iostream>

//unordered_map
#include <bits/stdc++.h>
#include <unordered_map>

#include "BookManager.h"
#include "Account.h"

using namespace std;

//Reads accounts file and passes data to data structures contained in Library.
class AccountFileReader {
public:
    bool readAccountFile(unordered_map<int, Account*> &umapAccount, string sAcctFileName, BookManager* pBookMgr);
    int printAccountFile(unordered_map<int, Account*> &umapAccount, BookManager* pBookMgr);
};

#endif //STACKOVERDUE_ACCOUNTFILEREADER_H
