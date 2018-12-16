//
// Created by WilliamUSER on 12/9/2017.
//

#ifndef STACKOVERDUE_ACCOUNTMANAGER_H
#define STACKOVERDUE_ACCOUNTMANAGER_H
#include <iomanip>
#include <fstream>
#include <iostream>

//unordered_map
#include <bits/stdc++.h>
#include <unordered_map>

#include "BookManager.h"
#include "Account.h"

class AccountManager {
private:
    unordered_map<int, Account*> umapAccount;
    set<int> setAcctID;
    multimap<string,int> mmapOfAcctName;
    multimap<int,int> mmapOfCheckout;

    BookManager* pBookMgr;
public:
    AccountManager(BookManager* bookManager) {
        pBookMgr=bookManager;
    }

    unordered_map<int,Account*> getUmapAccount() {return umapAccount;}
    bool loadAccounts(string sAcctFileName);
    void createAcctIndices();
    bool isAcctMgrEmpty();

    void browseAccountsByName();
    void browseAccountsByAccountid();
    void browseAccountsByCheckouts();

    Account* getAnAccount(int iAcctID);
    int getTotalNumAccounts();
    int getTotalNumAccountsOverdue();
    int updateOverdue(int acctID);

    void DeleteEntryInmmapOfCheckout (int oldCheckoutVal,int acctID);
    void DeleteEntryInmmapOfAcctName (string userName,int acctID);
    void UpdatemmapOfCheckout (int acctID, int oldCheckoutVal, int newCheckoutVal);

    bool addAnAcct(string userName);
    bool removeAnAcct(int acctID);
};

#endif //STACKOVERDUE_ACCOUNTMANAGER_H
