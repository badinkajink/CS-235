//
// Created by WilliamUSER on 12/8/2017.
//

#ifndef STACKOVERDUE_BOOK_H
#define STACKOVERDUE_BOOK_H

#include <iostream>
using namespace std; // make std members visible

enum BooksOrderType { TITLE, AUTHOR, GENRE, BOOKID, POPULARITY };

class Book {
private:
    int iBookID;
    string sTitle;
    string sAuthor;
    string sGenre;
    int iPopScore;

    int iDueDate;
    int iRenewals;
    bool bIsCheckedOut;
    int iAcctID;
public:
    Book(int bookId, string title, string author, string genre, int popScore) {
        iBookID=bookId;
        sTitle=title;
        sAuthor=author;
        sGenre=genre;
        iPopScore=popScore;

        bIsCheckedOut=false;
        iRenewals=0;
    }

    int getBookID () { return iBookID;}
    string getTitle () { return sTitle;}
    string getAuthor () { return sAuthor;}
    string getGenre () { return sGenre;}

    int getPopScore () { return iPopScore;}
    void setPopScore (int score) { iPopScore=score;}

    int getDueDate () { return iDueDate;}
    int getRenewals (){ return iRenewals;}
    bool getIsCheckedOut () { return bIsCheckedOut;}
    int getAcctID () { return iAcctID;}

    void setDueDate (int dueDate) {iDueDate = dueDate;}
    void setRenewals (int renewal) {iRenewals=renewal;}
    void setIsCheckedOut (bool checkedOut) {bIsCheckedOut=checkedOut;}
    void setAcctID (int acctID) {iAcctID = acctID;}
};

#endif //STACKOVERDUE_BOOK_H
