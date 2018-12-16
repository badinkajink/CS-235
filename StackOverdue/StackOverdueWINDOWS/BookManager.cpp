//
// Created by WilliamUSER on 12/9/2017.
//

#include <iomanip>
#include <fstream>
#include <iostream>
#include <stack>

//unordered_map
#include <bits/stdc++.h>

#include "Time.h"
#include "Book.h"
#include "BookFileReader.h"
#include "BookManager.h"

bool BookManager::loadBooks(string sBookFileName) {
    BookFileReader bookReader;

    bookReader.readBookFile(umapBook,sBookFileName);

//    bookReader.printBookFile(umapBook);

    createBookIndices();

    return true;
}

void BookManager::createBookIndices() {
    int iBookID;
    string sTitle;
    string sAuthor;
    string sGenre;
    int iPopScore;

//    cout <<"\n\n In BookManager CreateIndices\n";
    unordered_map<int , Book*>:: iterator itrBk;
    for (itrBk = umapBook.begin(); itrBk != umapBook.end(); itrBk++)
    {
        Book* pTmpBook = itrBk->second;

        iBookID=pTmpBook->getBookID();
        sTitle=pTmpBook->getTitle();
        sAuthor=pTmpBook->getAuthor();
        sGenre=pTmpBook->getGenre();
        iPopScore=pTmpBook->getPopScore();

        setBookID.insert(iBookID);
        mmapOfTitle.insert( {sTitle,iBookID} );
        mmapOfAuthor.insert( {sAuthor,iBookID} );
        mmapOfGenre.insert( {sGenre,iBookID} );
        mmapOfPopScore.insert( {iPopScore,iBookID} );
    } // for loop itrbk
}

bool BookManager::isBookMgrEmpty() {
    if (setBookID.empty()) {
        return true;
    } else {
        return false;
    }
}

bool BookManager::isBookExisted(string title,string author) {
    bool bFound=false;
    int bookID;
    Book* pBook;
    multimap<string, int>::iterator itr;

    for (itr = mmapOfAuthor.begin(); itr != mmapOfAuthor.end(); itr++) {
        if (itr->first.compare(author) == 0) {
            bookID=itr->second;
            pBook=getABook(bookID);
            string sTitle=pBook->getTitle();
            if (sTitle.compare(title) == 0) {
                bFound=true;
            }
        }
    }
    return bFound;
}

void BookManager::browseBooksByTitle() {
    int count=1;
    // Iterate over the multimap using Iterator
    multimap<string, int>::iterator itr;
    for (itr = mmapOfTitle.begin(); itr != mmapOfTitle.end(); itr++) {
        int iBookID = itr->second;
        Book* pTmpBook=getABook(iBookID);

        if (pTmpBook) {
            cout <<count << ". \""<<pTmpBook->getTitle()<<"\" by "<<pTmpBook->getAuthor()<<" (BookID# "<<pTmpBook->getBookID()<<") ["<<pTmpBook->getGenre()<<"]. ";
            if (pTmpBook->getIsCheckedOut()){
                cout <<"CHECKED OUT (AccountID# "<<pTmpBook->getAcctID()<<").\n";
            } else {
                cout <<"AVAILABLE.\n";
            }
            count++;
        } // enf of if pTmpBook
    } // end of for loop for mmapOfTitle
}

void BookManager::browseBooksByAuthor() {
    int count=1;
    // Iterate over the multimap using Iterator
    multimap<string, int>::iterator itr;
    for (itr = mmapOfAuthor.begin(); itr != mmapOfAuthor.end(); itr++) {
        int iBookID = itr->second;
        Book* pTmpBook=getABook(iBookID);

        if (pTmpBook) {
            cout <<count << ". \""<<pTmpBook->getTitle()<<"\" by "<<pTmpBook->getAuthor()<<" (BookID# "<<pTmpBook->getBookID()<<") ["<<pTmpBook->getGenre()<<"]. ";
            if (pTmpBook->getIsCheckedOut()){
                cout <<"CHECKED OUT (AccountID# "<<pTmpBook->getAcctID()<<").\n";
            } else {
                cout <<"AVAILABLE.\n";
            }
            count++;
        } // end of if pTmpBook
    } // end of for loop mmapOfAuthor
}

void BookManager::browseBooksByGenre() {
    int count=1;
    // Iterate over the multimap using Iterator
    multimap<string, int>::iterator itr;
    for (itr = mmapOfGenre.begin(); itr != mmapOfGenre.end(); itr++) {
        int iBookID = itr->second;
        Book* pTmpBook=getABook(iBookID);

        if (pTmpBook) {
            cout << count << ". \"" << pTmpBook->getTitle() << "\" by " << pTmpBook->getAuthor() << " (BookID# "
                 << pTmpBook->getBookID() << ") [" << pTmpBook->getGenre() << "]. ";
            if (pTmpBook->getIsCheckedOut()) {
                cout << "CHECKED OUT (AccountID# " << pTmpBook->getAcctID() << ").\n";
            } else {
                cout << "AVAILABLE.\n";
            }
            count++;
        } // end of if pTmpBook
    } // end of for loop mmapOfGenre
}

void BookManager::browseBooksByBookid() {
    int count=1;
    // Iterate over the set using Iterator
    set<int>::iterator itr;
    for (itr=setBookID.begin(); itr!=setBookID.end(); ++itr) {
        int iBookID = *itr;
        Book* pTmpBook=getABook(iBookID);

        if (pTmpBook) {
            cout <<count << ". \""<<pTmpBook->getTitle()<<"\" by "<<pTmpBook->getAuthor()<<" (BookID# "<<pTmpBook->getBookID()<<") ["<<pTmpBook->getGenre()<<"]. ";
            if (pTmpBook->getIsCheckedOut()){
                cout <<"CHECKED OUT (AccountID# "<<pTmpBook->getAcctID()<<").\n";
            } else {
                cout <<"AVAILABLE.\n";
            }
            count++;
        } // end of if pTmpBook
    } // end of for loop setBookID
}

// popularity score ordering is descending.  The reverse iterator is used to accomplished that.
void BookManager::browseBooksByPopularity() {
    int count=1;
    // Iterate over the multimap using Iterator
    multimap<int, int>::reverse_iterator ritr;
    for (ritr = mmapOfPopScore.rbegin(); ritr != mmapOfPopScore.rend(); ritr++) {
        int iBookID = ritr->second;
        Book* pTmpBook=getABook(iBookID);

        if (pTmpBook) {
            cout <<count << ". \""<<pTmpBook->getTitle()<<"\" by "<<pTmpBook->getAuthor()<<" (BookID# "<<pTmpBook->getBookID()<<") ["<<pTmpBook->getGenre()<<"]. ";
            if (pTmpBook->getIsCheckedOut()){
                cout <<"CHECKED OUT (AccountID# "<<pTmpBook->getAcctID()<<").\n";
            } else {
                cout <<"AVAILABLE.\n";
            }
            count++;
        } // end of if pTmpBook
    } // end of for looop mmapOfPopScore
}

// Return the pointer to the book for a found bookID.  If not found, a NULL pointer will be returned.
Book* BookManager::getABook(int iBookID) {
    Book* pBook= NULL;

    unordered_map<int, Book*>::const_iterator itrBk = umapBook.find (iBookID);
    if ( itrBk != umapBook.end() ) {
        pBook = itrBk->second;
    }

    return pBook;
}

int BookManager::getTotalNumBooks() {
    return setBookID.size();
}

int BookManager::getTotalNumBooksOverdue() {
    int numBooksOverdue=0;

    // Iterate over the set using Iterator
    set<int>::iterator itr;
    for (itr=setBookID.begin(); itr!=setBookID.end(); ++itr) {
        int iAcctID = *itr;

        Book* pBook=getABook(iAcctID);
        if (pBook->getIsCheckedOut()) {
            if (Time::getTime() > (unsigned int) pBook->getDueDate()) {
                numBooksOverdue++;
            }
        }
    }
    return numBooksOverdue;
}

void BookManager::DeleteEntryInmmapOfTitle (string title,int bookID) {
    bool bFound=false;
    multimap<string, int>::iterator itr, save_it;
    for (itr = mmapOfTitle.begin(); itr != mmapOfTitle.end(); itr++) {
        if ( (itr->first.compare(title) == 0) && (itr->second == bookID) ) {
            save_it = itr;
            bFound=true;
        }
    }
    //remove the old entry at the iterator position from the multimap "mmapOfTitle".
    if (bFound)
        mmapOfTitle.erase(save_it);
}

void BookManager::DeleteEntryInmmapOfAuthor (string author,int bookID){
    bool bFound=false;
    multimap<string, int>::iterator itr, save_it;
    for (itr = mmapOfAuthor.begin(); itr != mmapOfAuthor.end(); itr++) {
        if ( (itr->first.compare(author) == 0) && (itr->second == bookID) ) {
            save_it = itr;
            bFound=true;
        }
    }
    //remove the old entry at the iterator position from the multimap "mmapOfAuthor".
    if (bFound)
        mmapOfAuthor.erase(save_it);
}

void BookManager::DeleteEntryInmmapOfGenre (string genre,int bookID) {
    bool bFound=false;
    multimap<string, int>::iterator itr, save_it;
    for (itr = mmapOfGenre.begin(); itr != mmapOfGenre.end(); itr++) {
        if ( (itr->first.compare(genre) == 0) && (itr->second == bookID) ) {
            save_it = itr;
            bFound=true;
        }
    }
    //remove the old entry at the iterator position from the multimap "mmapOfGenre".
    if (bFound)
        mmapOfGenre.erase(save_it);
}

void BookManager::DeleteEntryInmmapOfPopScore (int popscore,int bookID) {
    bool bFound=false;
    multimap<int, int>::iterator itr, save_it;
    for (itr = mmapOfPopScore.begin(); itr != mmapOfPopScore.end(); itr++) {
        if ( (itr->first == popscore) && (itr->second == bookID) ) {
            save_it = itr;
            bFound=true;
        }
    }
    //remove the old entry at the iterator position from the multimap "mmapOfPopScore".
    if (bFound)
        mmapOfPopScore.erase(save_it);
}

//update book manager's multimap "mmapOfPopScore" to reflect the change in the popularity score.
//Remove the mmap entry (oldPopScore, bookID)
//then add the mmap entry (newPopScore, bookID)
void BookManager::UpdatemmapOfPopScore (int bookID, int oldPopScore, int newPopScore) {
    //remove the old entry at the iterator position from the multimap "mmapOfPopScore".
    DeleteEntryInmmapOfPopScore(oldPopScore,bookID);
    //insert the entry to the multimap "mmapOfPopScore".
    mmapOfPopScore.insert( {newPopScore,bookID});
}

void BookManager::searchAllBooks() {
    int count=1;
    unordered_map<int , Book*>:: iterator itrBk;
    for (itrBk = umapBook.begin(); itrBk != umapBook.end(); itrBk++)
    {
        Book* pTmpBook = itrBk->second;

        cout <<count << ". \""<<pTmpBook->getTitle()<<"\" by "<<pTmpBook->getAuthor()<<" (BookID# "<<pTmpBook->getBookID()<<") ["<<pTmpBook->getGenre()<<"]. ";
        if (pTmpBook->getIsCheckedOut()){
            cout <<"CHECKED OUT (AccountID# "<<pTmpBook->getAcctID()<<").\n";
        } else {
            cout <<"AVAILABLE.\n";
        }
        count++;
    }
}

void BookManager::searchBooksByTitle(string searchWord) {
    int count = 1;

    unordered_map<int , Book*>:: iterator itrBk;
    for (itrBk = umapBook.begin(); itrBk != umapBook.end(); itrBk++)
    {
        Book* pTmpBook = itrBk->second;
        string sTitle=pTmpBook->getTitle();

        size_t found = sTitle.find(searchWord);
        if (found!=string::npos) {
            cout <<count << ". \""<<pTmpBook->getTitle()<<"\" by "<<pTmpBook->getAuthor()<<" (BookID# "<<pTmpBook->getBookID()<<") ["<<pTmpBook->getGenre()<<"]. ";
            if (pTmpBook->getIsCheckedOut()){
                cout <<"CHECKED OUT (AccountID# "<<pTmpBook->getAcctID()<<").\n";
            } else {
                cout <<"AVAILABLE.\n";
            }
            count++;
        } // found the substr searchWord in the title
    } // for loop for the whole book unordered map

    if (count == 1) {
        cout <<"No search results found.\n";
    }
}

void BookManager::searchBooksByAuthor(string searchWord) {
    int count=1;

    unordered_map<int , Book*>:: iterator itrBk;
    for (itrBk = umapBook.begin(); itrBk != umapBook.end(); itrBk++)
    {
        Book* pTmpBook = itrBk->second;
        string sAuthor=pTmpBook->getAuthor();

        size_t found = sAuthor.find(searchWord);
        if (found!=string::npos) {
            cout <<count << ". \""<<pTmpBook->getTitle()<<"\" by "<<pTmpBook->getAuthor()<<" (BookID# "<<pTmpBook->getBookID()<<") ["<<pTmpBook->getGenre()<<"]. ";
            if (pTmpBook->getIsCheckedOut()){
                cout <<"CHECKED OUT (AccountID# "<<pTmpBook->getAcctID()<<").\n";
            } else {
                cout <<"AVAILABLE.\n";
            }
            count++;
        } // found the substr searchWord in the author
    } // for loop for the whole book unordered map

    if (count == 1) {
        cout <<"No search results found.\n";
    }
}

bool BookManager::addABook(string title,string author,string genre) {

    int newBookID = 1;
    if (!setBookID.empty()) {
        // Since the set is ordered. The last element of the set for the BookManager has the largest value.
        // set the new Book ID to be the current largest Book ID + 1.
        newBookID = *setBookID.rbegin() + 1;
    }

    //create the Book object.
    Book* pBook = new Book(newBookID,title,author,genre,0);
    //insert the Book pointer to the unordered map "umapBook".
    umapBook.insert( { newBookID,pBook });

    //insert the new book ID to set "setBookID".
    setBookID.insert(newBookID);
    //insert the title to the multimap "mmapOfTitle".
    mmapOfTitle.insert( {title,newBookID} );
    //insert the author to the multimap "mmapOfAuthor".
    mmapOfAuthor.insert( {author,newBookID} );
    //insert the genre to the multimap "mmapOfGenre".
    mmapOfGenre.insert( {genre,newBookID} );
    //insert the value 0 to the multimap "mmapOfPopScore".
    mmapOfPopScore.insert( {0,newBookID} );

    cout<<"BookID# "<<newBookID<<" successfully created.\n";
    return true;
}

bool BookManager::removeABook(int bookID) {
    Book* pBook=getABook(bookID);

    //remove the old entry at the iterator position from the multimap "mmapOfTitle".
    DeleteEntryInmmapOfTitle (pBook->getTitle(),bookID);
    //remove the old entry at the iterator position from the multimap "mmapOfAuthor".
    DeleteEntryInmmapOfAuthor (pBook->getAuthor(),bookID);
    //remove the old entry at the iterator position from the multimap "mmapOfGenre".
    DeleteEntryInmmapOfGenre (pBook->getGenre(),bookID);
    //remove the old entry at the iterator position from the multimap "mmapOfPopScore".
    DeleteEntryInmmapOfPopScore (pBook->getPopScore(),bookID);

    umapBook.erase(bookID);
    setBookID.erase(bookID);

    return true;
}
