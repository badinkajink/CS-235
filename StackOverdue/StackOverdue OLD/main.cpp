//
// Created by WilliamUSER on 12/8/2017.
//
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

void displayHelpMsg () {
    cout <<"BROWSE: Provides the status of all the books."<<endl;
    cout <<"BOOK: Provides the status of a specific book."<<endl;
    cout <<"SEARCH: Searches for all books with a key-phrase in the title or author."<<endl;
    cout <<"ACCOUNTS: Provides account snapshots for all user accounts."<<endl;
    cout <<"ACCOUNT: Provides an account snapshot for a specific user account."<<endl;
    cout <<"CHECKOUT: Checks a book out to a user account."<<endl;
    cout <<"RENEW: Renews a checked out book. (Up to two times allowed)"<<endl;
    cout <<"RETURN: Returns a checked out book."<<endl;
    cout <<"RECOMMEND: Generates a list of recommended books for a given user."<<endl;
    cout <<"ADDB: Adds a new book to the library."<<endl;
    cout <<"REMOVEB: Removes a specific book from the library."<<endl;
    cout <<"ADDA: Creates a new user account in the library."<<endl;
    cout <<"REMOVEA: Removes a specific user account from the library."<<endl;
    cout <<"SYSTEM: Provides diagnostic information about the system."<<endl;
    cout <<"TIME: Fast forwards the system time by a specified number of days."<<endl;
    cout <<"EXPORT: Exports the library’s books and accounts to files."<<endl;
    cout <<"HELP: Displays this help menu."<<endl;
    cout <<"EXIT: Exits the program."<<endl;
}

void stringToUpper(string &s)
{
    for(unsigned int l = 0; l < s.length(); l++)
    {
        s[l] = toupper(s[l]);
    }
}

enum CommandType { BROWSE, BOOK, SEARCH, ACCOUNTS, ACCOUNT, CHECKOUT, RENEW, RETURN, RECOMMEND, ADDB, REMOVEB, ADDA, REMOVEA, SYSTEM, TIME, EXPORT, HELP, EXIT };
bool intepretCommand (string &command, CommandType &cmdType) {

    stringToUpper(command);

    if (command.compare("BROWSE") == 0) {
        cmdType = BROWSE;
    } else if (command.compare("BOOK") == 0) {
        cmdType = BOOK;
    } else if (command.compare("SEARCH") == 0) {
        cmdType = SEARCH;
    } else if (command.compare("ACCOUNTS") == 0) {
        cmdType = ACCOUNTS;
    } else if (command.compare("ACCOUNT") == 0) {
        cmdType = ACCOUNT;
    } else if (command.compare("CHECKOUT") == 0) {
        cmdType = CHECKOUT;
    } else if (command.compare("RENEW") == 0) {
        cmdType = RENEW;
    } else if (command.compare("RETURN") == 0) {
        cmdType = RETURN;
    } else if (command.compare("RECOMMEND") == 0) {
        cmdType = RECOMMEND;
    } else if (command.compare("ADDB") == 0) {
        cmdType = ADDB;
    } else if (command.compare("REMOVEB") == 0) {
        cmdType = REMOVEB;
    } else if (command.compare("ADDA") == 0) {
        cmdType = ADDA;
    } else if (command.compare("REMOVEA") == 0) {
        cmdType = REMOVEA;
    } else if (command.compare("SYSTEM") == 0) {
        cmdType = SYSTEM;
    } else if (command.compare("TIME") == 0) {
        cmdType = TIME;
    } else if (command.compare("EXPORT") == 0) {
        cmdType = EXPORT;
    } else if (command.compare("HELP") == 0) {
        cmdType = HELP;
    } else if (command.compare("EXIT") == 0) {
        cmdType = EXIT;
    } else {
        // no recognized command was entered.
        return false;
    }
    return true;
}

int readCommands () {
    string input = "";
    string command="";
    CommandType cmdType=BROWSE;

    cout << "> ";
    while (cmdType != EXIT) {
        getline(cin, input);

        stringstream myStream(input);
        if (myStream >> command) {
            if (intepretCommand(command, cmdType)) {
                switch(cmdType) {
                    case BROWSE :
                        break;
                    case BOOK :
                        break;
                    case SEARCH :
                        break;
                    case ACCOUNTS :
                        break;
                    case ACCOUNT :
                        break;
                    case CHECKOUT :
                        break;
                    case RENEW :
                        break;
                    case RETURN :
                        break;
                    case RECOMMEND :
                        break;
                    case ADDB :
                        break;
                    case REMOVEB :
                        break;
                    case ADDA :
                        break;
                    case REMOVEA :
                        break;
                    case SYSTEM :
                        break;
                    case TIME :
                        break;
                    case EXPORT :
                        break;
                    case HELP :
                        displayHelpMsg();
                        break;
                    case EXIT :
                        break;
                    default :
                        break;
                }

                cout << "\n> ";
            } else {
                //no recognized comamnd was entered.
                cout <<"Invalid comamnd.\n\n";
                cout << "> ";
            }
        } else {
            // no string was entered on the command line.
            cout <<"Invalid comamnd.\n\n";
            cout << "> ";
        }
    }

    return 0;
} // while loop for cmdType

// Initialize static member of class Time
unsigned int Time::uiTime = 1;

int main(int argc, char* argv[]) {
    string sBookFileName="";
    string sAccountFileName="";
    unordered_map<int, Book*> umapBooks;
    unordered_map<int, Account*> umapAccounts;

    BookManager* bookMgr=new BookManager;
    AccountManager* acctMgr=new AccountManager(bookMgr);

    switch(argc) {
        case 1 :
            break;
        case 2 :
            sBookFileName = argv[1];
            break;
        case 3 :
            sBookFileName = argv[1];
            sAccountFileName = argv[2];
            break;
        default :
            sBookFileName = argv[1];
            sAccountFileName = argv[2];
            break;
    }

    bookMgr->loadBooks(umapBooks,sBookFileName);
    acctMgr->loadAccounts(umapAccounts,sAccountFileName);

    readCommands();

/*
    unordered_map<int, Book> umapBook;
    Book bBook1 = {1,"Basketball1","Kurt Vonnegut1","Fiction1",11};
    Book bBook2 = {2,"Basketball2","Kurt Vonnegut2","Fiction2",12};
    Book bBook3 = {3,"Basketball3","Kurt Vonnegut3","Fiction3",13};

    cout << "Book ID: "<<bBook1.getId()<<"; Title: "<<bBook1.getTitle()<<"\n";
    cout << "Book ID: "<<bBook2.getId()<<"; Title: "<<bBook2.getTitle()<<"\n";
    cout << "Book ID: "<<bBook3.getId()<<"; Title: "<<bBook3.getTitle()<<"\n";

    umapBook[1]=bBook;
    umapBook.insert( { 1,bBook1 });
    umapBook.insert( { 2,bBook2 });
    umapBook.insert( { 3,bBook3 });
*/

/*
    unordered_map<int, Book*> umapBook;
    Book* pBook1 = new Book(1,"Basketball1","Kurt Vonnegut1","Fiction1",11);
    Book* pBook2 = new Book(2,"Basketball2","Kurt Vonnegut2","Fiction2",12);
    Book* pBook3 = new Book(3,"Basketball3","Kurt Vonnegut3","Fiction3",13);
    Book* pBook4 = new Book(2,"Basketball2","Kurt Vonnegut4","Fiction3",14);

    umapBook.insert( { 1,pBook1 });
    umapBook.insert( { 2,pBook2 });
    umapBook.insert( { 3,pBook3 });

//    unordered_map<int , Book>:: iterator itrB;
    unordered_map<int , Book*>:: iterator itrB;
    cout << "\nAll Elements : \n";
    for (itrB = umapBook.begin(); itrB != umapBook.end(); itrB++)
    {
        int key = itrB->first;
//        Book tmpBook = itrB->second;
        Book* pTmpBook = itrB->second;

//        cout << itrB->first << " " << tmpBook.getTitle() << endl;
        cout << itrB->first << " " << pTmpBook->getTitle() << endl;
    }
*/

/*
    // multimap example
    multimap<int, Book*> mmapOfPos;
    mmapOfPos.insert( { 1,pBook1 });
    mmapOfPos.insert( { 2,pBook2 });
    mmapOfPos.insert( { 3,pBook3 });
    mmapOfPos.insert( { 2,pBook4 });

    multimap<int, Book*>:: iterator itrMB;
    cout << "\nAll Elements in Multimap: \n";
    for (itrMB = mmapOfPos.begin(); itrMB != mmapOfPos.end(); itrMB++)
    {
        int key = itrMB->first;
        Book* pTmpBook = itrMB->second;

        cout << itrMB->first << " " << pTmpBook->getTitle() << endl;
    }
*/

/*
// first example use of unorder map.
    unordered_map<string, double> umap;
    // inserting values by using [] operator

    umap["PI"] = 3.14;
    umap["root2"] = 1.414;
    umap["root3"] = 1.732;
    umap["log10"] = 2.302;
    umap["loge"] = 1.0;
    umap["PI"] = 5.14;

    // inserting value by insert function
    umap.insert(make_pair("e", 2.718));

    string key = "PI";

    // If key not found in map iterator to end is returned
    if (umap.find(key) == umap.end())
        cout << key << " not found\n\n";

        // If key found then iterator to that key is returned
    else
        cout << "Found " << key << "\n\n";

    key = "lambda";
    if (umap.find(key) == umap.end())
        cout << key << " not found\n";
    else
        cout << "Found " << key << endl;

    //    iterating over all value of umap
    unordered_map<string, double>:: iterator itr;
    cout << "\nAll Elements : \n";
    for (itr = umap.begin(); itr != umap.end(); itr++)
    {
        // itr works as a pointer to pair<string, double>
        // type itr->first stores the key part  and
        // itr->second stroes the value part
        cout << itr->first << "  " << itr->second << endl;
    }
*/

/*
// second example use of unorder map.
    string str = "geeks for geeks geeks quiz "
            "practice qa for";

    unordered_map<string, int> wordFreq;

    // breaking input into word using string stream
    istringstream ss(str);  // Used for breaking words
    string word; // To store individual words
    while (ss >> word)
        wordFreq[word] = wordFreq[word]+1;
//    wordFreq[word]++;

    // now iterating over word, freq pair and printing
    // them in <, > format
    unordered_map<string, int>:: iterator p;
    for (p = wordFreq.begin(); p != wordFreq.end(); p++)
        cout << "(" << p->first << ", " << p->second << ")\n";

*/

    return 0;
}
