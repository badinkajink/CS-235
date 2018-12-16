//
// Created by WilliamUSER on 12/8/2017.
//

#ifndef STACKOVERDUE_ACCOUNT_H
#define STACKOVERDUE_ACCOUNT_H

#include <iostream>
#include <vector>

//unordered_map
#include <bits/stdc++.h>

using namespace std; // make std members visible

enum AccountsOrderType { NAME, ACCOUNTID, CHECKOUTS };

class Account {
private:
    int iAcctID;
    string sUserName;
    int iNumCheckedOut;

    int iOverdue;
    set<int> *psetCheckedOutBooks;
    set<int> *psetCheckedOutBooksHistory;
public:
    Account(int acctID, string userName, int num) {
        iAcctID=acctID;
        sUserName=userName;
        iNumCheckedOut=num;

        iOverdue=0;
        psetCheckedOutBooks= NULL;
        psetCheckedOutBooksHistory= NULL;
    }

    int getAccountID () { return iAcctID;}
    string getUserName () {return sUserName;}
    int getNumCheckedOut () { return iNumCheckedOut;}
    void setNumCheckedOut (int num) { iNumCheckedOut=num;}

    int getOverdue () {return iOverdue;}
    void setOverdue (int overdue) {iOverdue=overdue;}

    set<int>* getCheckedOutBooks() { return psetCheckedOutBooks;}
    set<int>* getCheckedOutBooksHistory() { return psetCheckedOutBooksHistory;}
    void setCheckedOutBooks(set<int>* pCheckedOut) {psetCheckedOutBooks=pCheckedOut;}
    void setCheckedOutBooksHistory(set<int>* pHistory) {psetCheckedOutBooksHistory=pHistory;}
};

#endif //STACKOVERDUE_ACCOUNT_H
