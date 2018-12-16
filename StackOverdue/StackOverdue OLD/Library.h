//
// Created by WilliamUSER on 12/10/2017.
//

#ifndef STACKOVERDUE_LIBRARY_H
#define STACKOVERDUE_LIBRARY_H

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

using namespace std; // make std members visible


class Library {
private:
    string sBookFileName;
    string sAccountFileName;
    BookManager* bookMgr;
    AccountManager* acctMgr;

public:
    void initializeLibrary(string bookFileName, string accountFileName);
    BookManager* getBookMgr() { return bookMgr;}
    AccountManager* getAcctMgr () { return acctMgr;}

    bool browseBooks (BooksOrderType sortOrderType);
    bool printABook (int bookID);
    bool searchBooks(BooksOrderType searchType,string searchWord);

    bool browseAccounts(AccountsOrderType sortOrderType);
    bool printAnAccount(int accountID);
    bool CheckoutABook(int accountID, int bookID);
    bool renewBooks(int accountID);
    bool returnABook(int bookID);

    bool recommendBooks(int accountID);
    void printRecommendedBooks(int bookID, int pos);

    bool addABook(string title,string author,string genre);
    bool removeABook(int bookID);
    bool addAnAcct(string userName);
    bool removeAnAcct(int acctID);
    bool systemInfo();
    void timeTravel (unsigned int uiTravel);
    bool exportToBookfile(string bookFilename);
    bool exportToAcctfile(string acctFilename);
    void exportToFiles(string bookFilename,string acctFilename);

    void displayHelpMsg ();
    void displayExitMsg ();
};

#endif //STACKOVERDUE_LIBRARY_H
