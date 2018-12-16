//
// Created by WilliamUSER on 12/10/2017.
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
#include "Administrator.h"


void Administrator::stringToUpper(string &s) {
    for(unsigned int i = 0; i < s.length(); i++)
    {
        s[i] = toupper(s[i]);
    }
}

bool Administrator::intepretCommand (string &command, CommandType &cmdType) {
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

int Administrator::runCommands () {
    string input = "";
    string command="";
    CommandType cmdType=BROWSE;

    while (cmdType != EXIT) {
        cout << "\n> ";
        getline(cin, input);

        stringstream myStream(input);
        if (myStream >> command) {
            if (intepretCommand(command, cmdType)) {
                switch(cmdType) {
                    case BROWSE : {
                        if (myLibrary.getBookMgr()->isBookMgrEmpty()) {
                            cout<<"No books in your library.\n";
                        } else {
                            BooksOrderType sortOrderType;
                            if (parseBrowse(sortOrderType))
                                myLibrary.browseBooks(sortOrderType);
                        }
                    } // case BROWSE
                        break;
                    case BOOK : {
                        if (myLibrary.getBookMgr()->isBookMgrEmpty()) {
                            cout<<"No books in your library.\n";
                        } else {
                            int bookID;
                            if (parseBook(bookID))
                                myLibrary.printABook(bookID);
                        }
                    }
                        break;
                    case SEARCH : {
                        if (myLibrary.getBookMgr()->isBookMgrEmpty()) {
                            cout<<"No books in your library.\n";
                        } else {
                            BooksOrderType searchType;
                            string searchWord = "";
                            if (parseSearch(searchType, searchWord))
                                myLibrary.searchBooks(searchType, searchWord);
                        }
                    }
                        break;
                    case ACCOUNTS : {
                        if (myLibrary.getAcctMgr()->isAcctMgrEmpty()) {
                            cout<<"No accounts in your library.\n";
                        } else {
                            AccountsOrderType sortOrderType;
                            if (parseAccounts(sortOrderType))
                                myLibrary.browseAccounts(sortOrderType);
                        }
                    }
                        break;
                    case ACCOUNT : {
                        if (myLibrary.getAcctMgr()->isAcctMgrEmpty()) {
                            cout<<"No accounts in your library.\n";
                        } else {
                            int accountID;
                            if (parseAccount(accountID))
                                myLibrary.printAnAccount(accountID);
                        }
                    }
                        break;
                    case CHECKOUT : {
                        if (myLibrary.getAcctMgr()->isAcctMgrEmpty()) {
                            cout<<"No accounts in your library.\n";
                        } else {
                            int accountID, bookID;
                            if (parseCheckout(accountID, bookID))
                                myLibrary.CheckoutABook(accountID, bookID);
                        }
                    }
                        break;
                    case RENEW : {
                        if (myLibrary.getAcctMgr()->isAcctMgrEmpty()) {
                            cout<<"No accounts in your library.\n";
                        } else {
                            int accountID;
                            if (parseRenew(accountID))
                                myLibrary.renewBooks(accountID);
                        }
                    }
                        break;
                    case RETURN : {
                        if (myLibrary.getBookMgr()->isBookMgrEmpty()) {
                            cout<<"No books in your library.\n";
                        } else {
                            int bookID;
                            if (parseReturn(bookID))
                                myLibrary.returnABook(bookID);
                        }
                    }
                        break;
                    case RECOMMEND : {
                        if (myLibrary.getAcctMgr()->isAcctMgrEmpty()) {
                            cout<<"No accounts in your library.\n";
                        } else {
                            int accountID;
                            if (parseRecommend(accountID))
                                myLibrary.recommendBooks(accountID);
                        }
                    }
                        break;
                    case ADDB : {
                        string title="", author="", genre="";
                        if (parseAddb(title,author,genre))
                            myLibrary.addABook(title,author,genre);
                    }
                        break;
                    case REMOVEB : {
                        if (myLibrary.getBookMgr()->isBookMgrEmpty()) {
                            cout<<"No books in your library.\n";
                        } else {
                            int bookID;
                            if (parseRemoveb(bookID))
                                myLibrary.removeABook(bookID);
                        }
                    }
                        break;
                    case ADDA : {
                        string userName="";
                        if (parseAdda(userName))
                            myLibrary.addAnAcct(userName);
                    }
                        break;
                    case REMOVEA : {
                        if (myLibrary.getAcctMgr()->isAcctMgrEmpty()) {
                            cout<<"No accounts in your library.\n";
                        } else {
                            int acctID;
                            if (parseRemovea(acctID))
                                myLibrary.removeAnAcct(acctID);
                        }
                    }
                        break;
                    case SYSTEM : {
                        if (parseSystem())
                            myLibrary.systemInfo();
                    }
                        break;
                    case TIME : {
                        unsigned int uiTravel;
                        if (parseTime(uiTravel))
                            myLibrary.timeTravel(uiTravel);
                    }
                        break;
                    case EXPORT : {
                        string bookFilename="", acctFilename="";
                        if (parseExport(bookFilename,acctFilename))
                            myLibrary.exportToFiles(bookFilename,acctFilename);
                    }
                        break;
                    case HELP :
                        myLibrary.displayHelpMsg();
                        break;
                    case EXIT :
                        myLibrary.displayExitMsg();
                        break;
                    default :
                        break;
                } // end of switch statement for cmdType
            } else {
                //no recognized comamnd was entered.
                cout <<"Invalid comamnd.\n";
            }
        } else {
            // no string was entered on the command line.
            cout <<"Invalid comamnd.\n";
        }
    } // while loop for cmdType

    return 0;
}

bool Administrator::parseBrowse(BooksOrderType &sortOrderType) {
    string input = "";
    cout << "Enter the criteria to sort by. (title/author/genre/bookid/popularity)\n";
    cout << "> ";
    getline(cin, input);

    string type;
    stringstream myStream(input);
    if (myStream >> type) {
        stringToUpper(type);
        if (type.compare("AUTHOR") == 0) {
            sortOrderType = AUTHOR;
        } else if (type.compare("TITLE") == 0) {
            sortOrderType = TITLE;
        } else if (type.compare("GENRE") == 0) {
            sortOrderType = GENRE;
        } else if (type.compare("BOOKID") == 0) {
            sortOrderType = BOOKID;
        } else if (type.compare("POPULARITY") == 0) {
            sortOrderType = POPULARITY;
        } else {
            // no valid sort order was entered.
            cout <<"Invalid value.\n";
            return false;
        }
        return true;
    } else {
        // no string was entered.
        cout <<"Invalid value.\n";
        return false;
    }
}

bool Administrator::parseBook(int &bookID) {
    string input = "";
    cout << "Enter the book id.\n";
    cout << "> ";
    getline(cin, input);

    int myNumber = 0;
    stringstream myStream(input);
    if (myStream >> myNumber) {
        bookID = myNumber;
        return true;
    } else {
        cout <<"Invalid input.\n";
        return false;
    }
}

bool Administrator::parseSearch(BooksOrderType &searchType, string &searchWord) {
    string input = "";
    cout << "Enter the criteria to search by. (title/author)\n";
    cout << "> ";
    getline(cin, input);

    string type;
    stringstream myStream(input);
    if (myStream >> type) {
        stringToUpper(type);
        if (type.compare("AUTHOR") == 0) {
            searchType = AUTHOR;
        } else if (type.compare("TITLE") == 0) {
            searchType = TITLE;
        } else {
            // neither author or title was entered.
            cout <<"Invalid value.\n";
            return false;
        }

        cout << "Enter the search phrase.\n";
        cout << "> ";
        getline(cin, input);
        stringstream ss(input);
        ss >> searchWord;

        return true;
    } else {
        // no string was entered.
        cout <<"Invalid value.\n";
        return false;
    }
}

bool Administrator::parseAccounts(AccountsOrderType &sortOrderType) {
    string input = "";
    cout << "Enter the criteria to sort by. (name/accountid/checkouts)\n";
    cout << "> ";
    getline(cin, input);

    string type;
    stringstream myStream(input);
    if (myStream >> type) {
        stringToUpper(type);
        if (type.compare("NAME") == 0) {
            sortOrderType = NAME;
        } else if (type.compare("ACCOUNTID") == 0) {
            sortOrderType = ACCOUNTID;
        } else if (type.compare("CHECKOUTS") == 0) {
            sortOrderType = CHECKOUTS;
        } else {
            // no valid sort order was entered.
            cout <<"Invalid value.\n";
            return false;
        }
        return true;
    } else {
        // no string was entered.
        cout <<"Invalid value.\n";
        return false;
    }
}

bool Administrator::parseAccount(int &accountID) {
    string input = "";
    cout << "Enter the account id.\n";
    cout << "> ";
    getline(cin, input);

    int myAccount = 0;
    stringstream myStream(input);
    if (myStream >> myAccount) {
        accountID = myAccount;
        return true;
    } else {
        cout <<"Invalid input.\n";
        return false;
    }
}

bool Administrator::parseCheckout(int &accountID, int &bookID) {
    string input = "";
    cout << "Enter the account id.\n";
    cout << "> ";
    getline(cin, input);

    stringstream myStream(input);
    if (myStream >> accountID) {
        cout << "Enter the book id.\n";
        cout << "> ";
        getline(cin, input);
        stringstream ss(input);
        if (ss >>bookID) {
            return true;
        } else {
            // invalid input for book id.
            cout <<"Invalid input.\n";
            return false;
        }
    } else {
        // invalid input for account id.
        cout <<"Invalid input.\n";
        return false;
    }
}

bool Administrator::parseRenew(int &accountID) {
    string input = "";
    cout << "Enter the account id.\n";
    cout << "> ";
    getline(cin, input);

    stringstream myStream(input);
    if (myStream >> accountID) {
        return true;
    } else {
        cout <<"Invalid input.\n";
        return false;
    }
}

bool Administrator::parseReturn(int &bookID) {
    string input = "";
    cout << "Enter the book id.\n";
    cout << "> ";
    getline(cin, input);

    stringstream myStream(input);
    if (myStream >> bookID) {
        return true;
    } else {
        cout <<"Invalid input.\n";
        return false;
    }
}

bool Administrator::parseRecommend(int &acctID) {
    string input = "";
    cout << "Enter the account id.\n";
    cout << "> ";
    getline(cin, input);

    stringstream myStream(input);
    if (myStream >> acctID) {
        return true;
    } else {
        cout <<"Invalid input.\n";
        return false;
    }
}

bool Administrator::parseAddb(string &title, string &author, string &genre) {
    string input = "";
    cout << "Enter the new book's title\n";
    cout << "> ";
    getline(cin, title);

    cout << "Enter the new book's author.\n";
    cout << "> ";
    getline(cin, author);

    if (myLibrary.getBookMgr()->isBookExisted(title, author)) {
        cout << "Book with this title and author already exists.\n";
        return false;
    } else {
        cout << "Enter the new book's genre.\n";
        cout << "> ";
        getline(cin, genre);
        return true;
    }
}

bool Administrator::parseRemoveb(int &bookID) {
    string input = "";
    cout << "Enter the book id.\n";
    cout << "> ";
    getline(cin, input);

    stringstream myStream(input);
    if (myStream >> bookID) {
        return true;
    } else {
        cout <<"Invalid input.\n";
        return false;
    }
}

bool Administrator::parseAdda(string &userName) {
    string input = "";
    cout << "Enter the new user's name.\n";
    cout << "> ";
    getline(cin, input);

    stringstream myStream(input);
    if (myStream >> userName) {
        return true;
    } else {
        cout <<"Invalid input.\n";
        return false;
    }
}

bool Administrator::parseRemovea(int &acctID) {
    string input = "";
    cout << "Enter the account id.\n";
    cout << "> ";
    getline(cin, input);

    stringstream myStream(input);
    if (myStream >> acctID) {
        return true;
    } else {
        cout <<"Invalid input.\n";
        return false;
    }
}

bool Administrator::parseSystem() {
    return true;
}

bool Administrator::parseTime(unsigned int &uiTravel) {
    string input = "";
    cout << "Enter the number of days to time travel.\n";
    getline(cin, input);

    int myNumber = 0;
    stringstream myStream(input);
    if (myStream >> myNumber) {
        uiTravel = myNumber;
        return true;
    } else {
        cout <<"Invalid value.\n";
        return false;
    }
}

bool Administrator::parseExport(string &bookFilename, string &acctFilename) {
    string input = "";
    cout << "Enter the name of the books file. (This may overwrite a file)\n";
    cout << "> ";
    getline(cin, input);

    stringstream ssBook(input);
    if (ssBook >> bookFilename) {
        cout << "Enter the name of the accounts file. (This may overwrite a file)\n";
        cout << "> ";
        getline(cin, input);
        stringstream ssAcct(input);
        if (ssAcct >> acctFilename) {
            return true;
        } else {
            // no string was entered for acctFilename.
            cout <<"Invalid value.\n";
            return false;
        }
    } else {
        // no string was entered for bookFilename.
        cout <<"Invalid value.\n";
        return false;
    }
}