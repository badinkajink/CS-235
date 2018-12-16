//
// Created by WilliamUSER on 12/10/2017.
//

#ifndef STACKOVERDUE_ADMINISTRATOR_H
#define STACKOVERDUE_ADMINISTRATOR_H

#include <iomanip>
#include <fstream>
#include <iostream>

//unordered_map
#include <bits/stdc++.h>

#include "Time.h"
#include "Book.h"
#include "Account.h"

#include "BookFileReader.h"
#include "BookManager.h"

#include "AccountFileReader.h"
#include "AccountManager.h"
#include "Library.h"

using namespace std; // make std members visible

enum CommandType { BROWSE, BOOK, SEARCH, ACCOUNTS, ACCOUNT, CHECKOUT, RENEW, RETURN, RECOMMEND, ADDB, REMOVEB, ADDA, REMOVEA, SYSTEM, TIME, EXPORT, HELP, EXIT };

class Administrator {
private:
    Library myLibrary;

public:
    Administrator(string bookFileName, string accountFileName) {
        myLibrary.initializeLibrary(bookFileName,accountFileName);
    }

    void stringToUpper(string &s);
    bool intepretCommand (string &command, CommandType &cmdType);
    int runCommands ();

    bool parseBrowse(BooksOrderType &sortOrderType);
    bool parseBook(int &bookID);
    bool parseSearch(BooksOrderType &searchType, string &searchWord);

    bool parseAccounts(AccountsOrderType &sortOrderType);
    bool parseAccount(int &accountID);
    bool parseCheckout(int &accountID, int &bookID);
    bool parseRenew(int &accountID);
    bool parseReturn(int &bookID);

    bool parseRecommend(int &acctID);

    bool parseAddb(string &title, string &author, string &genre);
    bool parseRemoveb(int &bookID);
    bool parseAdda(string &userName);
    bool parseRemovea(int &acctID);

    bool parseSystem();
    bool parseTime(unsigned int &uiTravel);
    bool parseExport(string &bookFilename, string &acctFilename);
};

#endif //STACKOVERDUE_ADMINISTRATOR_H
