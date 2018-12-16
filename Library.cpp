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
#include "Library.h"

void Library::initializeLibrary(string bookFileName, string accountFileName){
    sBookFileName=bookFileName;
    sAccountFileName=accountFileName;

    bookMgr=new BookManager;
    acctMgr=new AccountManager(bookMgr);

    bookMgr->loadBooks(sBookFileName);
    acctMgr->loadAccounts(sAccountFileName);
}

bool Library::browseBooks (BooksOrderType sortOrderType) {
    if (bookMgr->isBookMgrEmpty()) {
        cout<<"No books in your library.\n";
        return false;
    }

    switch(sortOrderType) {
        case TITLE :
            bookMgr->browseBooksByTitle();
            break;
        case AUTHOR :
            bookMgr->browseBooksByAuthor();
            break;
        case GENRE :
            bookMgr->browseBooksByGenre();
            break;
        case BOOKID :
            bookMgr->browseBooksByBookid();
            break;
        case POPULARITY :
            bookMgr->browseBooksByPopularity();
            break;
        default :
            break;
    }  // switch statement for sortOrderType

    return true;
}

bool Library::printABook(int bookID) {
    if (bookMgr->isBookMgrEmpty()) {
        cout<<"No books in your library.\n";
        return false;
    }

    Book* pBook = bookMgr->getABook(bookID);
    if (pBook) {
        cout<<"Title: \""<<pBook->getTitle()<<"\"\n";
        cout<<"Author: "<<pBook->getAuthor()<<"\n";
        cout<<"BookID#: "<<pBook->getBookID()<<"\n";
        cout<<"Genre: "<<pBook->getGenre()<<"\n";
        cout<<"Popularity Score: "<<pBook->getPopScore()<<"\n";

        if (pBook->getIsCheckedOut()){
            cout <<"Borrower AccountID#: "<<pBook->getAcctID()<<"\n";
            cout <<"Due Date: "<<pBook->getDueDate()<<"\n";
            cout <<"Times Renewed: "<<pBook->getRenewals()<<"\n";
            if (Time::getTime() > (unsigned int)pBook->getDueDate() )
                cout<<"OVERDUE\n";
        } else {
            cout <<"AVAILABLE\n";
        }
    } else {
        cout <<"BookID# "<<bookID<<" not found.\n";
    }

    return true;
}

bool Library::searchBooks(BooksOrderType searchType,string searchWord) {
    if (bookMgr->isBookMgrEmpty()) {
        cout<<"No books in your library.\n";
        return false;
    }

    if (searchWord == "") {
        bookMgr->searchAllBooks();
    } else {
        if (searchType == TITLE) {
            bookMgr->searchBooksByTitle(searchWord);
        } else if (searchType == AUTHOR) {
            bookMgr->searchBooksByAuthor(searchWord);
        }
    }

    return true;
}

bool Library::browseAccounts(AccountsOrderType sortOrderType) {
    if (acctMgr->isAcctMgrEmpty()) {
        cout<<"No accounts in your library.\n";
        return false;
    }

    switch(sortOrderType) {
        case NAME :
            acctMgr->browseAccountsByName();
            break;
        case ACCOUNTID :
            acctMgr->browseAccountsByAccountid();
            break;
        case CHECKOUTS :
            acctMgr->browseAccountsByCheckouts();
            break;
        default :
            break;
    }  // switch statement for sortOrderType

    return true;
}

bool Library::printAnAccount(int accountID) {
    if (acctMgr->isAcctMgrEmpty()) {
        cout<<"No accounts in your library.\n";
        return false;
    }

    Account* pAcct = acctMgr->getAnAccount(accountID);
    if (!pAcct) {
        cout <<"AccountID# "<<accountID<<" not found.\n";
        return false;

    } else {
        cout << "Name: " << pAcct->getUserName() << "\n";
        cout << "AccountID#: " << pAcct->getAccountID() << "\n";

        int numCheckout = pAcct->getNumCheckedOut();
        if (numCheckout == 0) {
            cout << "No books checked out.\n";

        } else if (numCheckout > 0) {
            int iOverdue =acctMgr->updateOverdue(accountID);
            if ( iOverdue == 0)
                cout << numCheckout << " books checked out:\n";
            else
                cout << numCheckout << " books checked out ("<<iOverdue<<" overdue):\n";

            set<int> *psetCheckedOutBooks = pAcct->getCheckedOutBooks();
            int iBookID;
            int cnt=1;
            // Iterate over the set using Iterator
            set<int>::iterator itr;
            for (itr=psetCheckedOutBooks->begin(); itr!=psetCheckedOutBooks->end(); ++itr) {
                iBookID = *itr;
                Book *pBook = bookMgr->getABook(iBookID);

                if (pBook) {
                    cout << "        " << cnt << ".\n";
                    cout << "        Title: \"" << pBook->getTitle() << "\"\n";
                    cout << "        Author: " << pBook->getAuthor() << "\n";
                    cout << "        BookID#: " << pBook->getBookID() << "\n";
                    cout << "        Genre: " << pBook->getGenre() << "\n";
                    cout << "        Popularity Score: " << pBook->getPopScore() << "\n";
                    cout << "        Due Date: " << pBook->getDueDate() << "\n";
                    cout << "        Times Renewed: " << pBook->getRenewals() << "\n";

                    if (Time::getTime() > (unsigned int) pBook->getDueDate()) {
                        cout << "        OVERDUE\n";
                    }
                } else {
                    cout << "BookID# " << iBookID << " not found.\n";
                }
                cnt++;
            } // end of for loop for psetCheckedOutBooks
        } // end of else if (numCheckout >0 )
    // end of if (pAcct)
    }

    return true;
}

// If the user has 10 books already checked out, has any overdue books, or the book is already checked out by someone else, they cannot check out any books
// Print a full description of the checked out book.
// Add the checkout book to the set of the checked out books for a given account.
// Add the checkout book to the set of the checked out books history for a given account, if it is checked out for the first time by this account.
// Increase the popularity score by 1 for the checkedout book if it is checked out for the first time by this account.
// Update the multimap mmapOfCheckout for the account manager, now that this account's number of checkout value is different.
bool Library::CheckoutABook(int accountID, int bookID) {
    if (acctMgr->isAcctMgrEmpty()) {
        cout<<"No accounts in your library.\n";
        return false;
    }

    Account* pAcct = acctMgr->getAnAccount(accountID);
    if (!pAcct) {
        cout << "AccountID# " << accountID << " not found.\n";
        return false;
    }

    if (acctMgr->updateOverdue(accountID) > 0) {
        cout <<"Account has books overdue.\n";
        return false;
    }

    if (pAcct->getNumCheckedOut() >=10 ) {
        cout <<"Account already has 10 books checked out.\n";
        return false;
    }

    Book* pBook = bookMgr->getABook(bookID);
    if (!pBook) {
        cout << "BookID# " << bookID << " not found.\n";
        return false;
    }

    if (pBook->getIsCheckedOut()) {
        cout << "Book already is checked out.\n";
        return false;
    }

    pBook->setIsCheckedOut(true);
    pBook->setAcctID(accountID);
    pBook->setRenewals(0);
    pBook->setDueDate(Time::getTime()+15);

    cout<<"Book successfully checked out.\n";
    cout<<"Title: \""<<pBook->getTitle()<<"\"\n";
    cout<<"Author: "<<pBook->getAuthor()<<"\n";
    cout<<"BookID#: "<<pBook->getBookID()<<"\n";
    cout<<"Genre: "<<pBook->getGenre()<<"\n";
    cout<<"Popularity Score: "<<pBook->getPopScore()<<"\n";
    cout <<"Due Date: "<<pBook->getDueDate()<<"\n";
    cout <<"Times Renewed: "<<pBook->getRenewals()<<"\n";

    set<int>* psetCheckOut=pAcct->getCheckedOutBooks();
    set<int>* psetCheckOutHistory=pAcct->getCheckedOutBooksHistory();

    //adding the BookID to the set of Checked out books for this account.
    psetCheckOut->insert(bookID);

    set<int>::iterator itr = psetCheckOutHistory->find(bookID);
    if (itr == psetCheckOutHistory->end()) {
        //This bookID is not found in the checkout history set.
        //add this bookID to the set of Checked out books history for this account.
        psetCheckOutHistory->insert(bookID);

        //update book manager's multimap "mmapOfPopScore" to reflect the increase in the popularity.
        bookMgr->UpdatemmapOfPopScore(bookID,pBook->getPopScore(),pBook->getPopScore()+1);

        //add 1 to the book's popularity score since this user never checked out this book before.
        pBook->setPopScore(pBook->getPopScore()+1);
        pBook->setIsCheckedOut(true);
    }

    int iNumCheckedOut=pAcct->getNumCheckedOut();
    pAcct->setNumCheckedOut(iNumCheckedOut+1);

    //update account manager's multimap "mmapOfCheckout" to reflect the change in the number of checkout.
    acctMgr->UpdatemmapOfCheckout(accountID,iNumCheckedOut,iNumCheckedOut+1);

    return true;
}

bool Library::renewBooks(int accountID) {
    if (acctMgr->isAcctMgrEmpty()) {
        cout<<"No accounts in your library.\n";
        return false;
    }

    Account* pAcct = acctMgr->getAnAccount(accountID);
    if (!pAcct) {
        cout << "AccountID# " << accountID << " not found.\n";
        return false;
    }

    if (acctMgr->updateOverdue(accountID) > 0) {
        cout <<"Account has books overdue.\n";
        return false;
    }

    if (pAcct->getNumCheckedOut() <=0 ) {
        cout << "No books on this account.\n";
        return false;
    }

    int numCheckOut = pAcct->getNumCheckedOut();
    set<int> *psetCheckedOutBooks = pAcct->getCheckedOutBooks();
    int iBookID;
    int iRenew=0;
    // Iterate over the set using Iterator
    set<int>::iterator itr;

    if ( numCheckOut > 0 ) {
        for (itr=psetCheckedOutBooks->begin(); itr!=psetCheckedOutBooks->end(); ++itr) {
            iBookID = *itr;
            Book *pBook = bookMgr->getABook(iBookID);
            if (pBook->getRenewals() < 2)
                iRenew++;
        }
        cout <<iRenew<<" of "<<numCheckOut<<" books successfully renewed.\n";

        int cnt=1;
        for (itr=psetCheckedOutBooks->begin(); itr!=psetCheckedOutBooks->end(); ++itr) {
            iBookID = *itr;
            bool bRenew=false;
            Book *pBook = bookMgr->getABook(iBookID);
            if (pBook) {
                if (pBook->getRenewals()<2 ) {
                    pBook->setDueDate(Time::getTime()+15);
                    pBook->setRenewals(pBook->getRenewals()+1);
                    bRenew=true;
                }
                cout << "        " << cnt << ".\n";
                cout << "        Title: \"" << pBook->getTitle() << "\"\n";
                cout << "        Author: " << pBook->getAuthor() << "\n";
                cout << "        BookID#: " << pBook->getBookID() << "\n";
                cout << "        Genre: " << pBook->getGenre() << "\n";
                cout << "        Popularity Score: " << pBook->getPopScore() << "\n";
                cout << "        Due Date: " << pBook->getDueDate() << "\n";
                cout << "        Times Renewed: " << pBook->getRenewals() << "\n";

                if (bRenew) {
                    cout << "        Book successfuly renewed.\n";
                } else {
                    cout << "        Book already renewed twice.\n";
                }
            } else {
                cout << "BookID# " << iBookID << " not found.\n";
            }
            cnt++;
        } // end of for loop for psetCheckedOutBooks
    } // end of if numCheckOut > 0
    return true;
}

bool Library::returnABook(int bookID) {
    if (bookMgr->isBookMgrEmpty()) {
        cout<<"No books in your library.\n";
        return false;
    }

    Book* pBook = bookMgr->getABook(bookID);
    if (!pBook) {
        cout << "BookID# " << bookID << " not found.\n";
        return false;
    }

    if (pBook->getIsCheckedOut() == false) {
        cout << "Book is not currently checked out.\n";
        return false;
    }

    int accountID =pBook->getAcctID();
    pBook->setIsCheckedOut(false);
    unsigned int dueDate = (unsigned int)pBook->getDueDate();
    if ( dueDate >= Time::getTime()) {
        cout<<"Book successfully returned by AccountID# "<<accountID<<" (on time).\n";
    } else {
        cout<<"Book successfully returned by AccountID# "<<accountID<<" (overdue by "<<(Time::getTime() - dueDate)<<" days).\n";
    }

    Account* pAcct = acctMgr->getAnAccount(accountID);
    if (!pAcct) {
        cout << "AccountID# " << accountID << " not found.\n";
        return false;
    }

    set<int>* psetCheckOut=pAcct->getCheckedOutBooks();
    //Delete the BookID from the set of Checked out books for this account.
    psetCheckOut->erase(bookID);

    //decrement the number of checked out by 1 for this account.
    int iNumCheckedOut=pAcct->getNumCheckedOut();
    pAcct->setNumCheckedOut(iNumCheckedOut-1);

    //update account manager's multimap "mmapOfCheckout" to reflect the change in the number of checkout.
    acctMgr->UpdatemmapOfCheckout(accountID,iNumCheckedOut,iNumCheckedOut-1);

    return true;
}

//First figure out the The most read author, mostReadAuthor, and  most read genres: mostReadGenre1 and mostReadGenre2,
// by using the set CheckedOutHistory for a given account.
bool Library::recommendBooks(int accountID) {
    if (acctMgr->isAcctMgrEmpty()) {
        cout<<"No accounts in your library.\n";
        return false;
    }

    Account* pAcct = acctMgr->getAnAccount(accountID);
    if (!pAcct) {
        cout << "AccountID# " << accountID << " not found.\n";
        return false;
    }

    set<int> *pHistory = pAcct->getCheckedOutBooksHistory();
    if (pHistory->size() == 0) {
        cout <<"No available recommendations.\n";
        return false;
    }

    multimap<string,int> mmapOfGenreCheckouts;
    multimap<string,int> mmapOfAuthorCheckouts;
    // Iterate over the set using Iterator
    set<int>::iterator itr;
    for (itr=pHistory->begin(); itr!=pHistory->end(); ++itr) {
        int iBookID = *itr;
        Book *pBook = bookMgr->getABook(iBookID);
        if (pBook) {
            string author = pBook->getAuthor();
            string genre = pBook->getGenre();

            //insert the book ID to the multimap "mmapOfGenre" sorted by author.
            mmapOfAuthorCheckouts.insert( {author,iBookID} );
            //insert the book ID to the multimap "mmapOfGenre" sorted by genre.
            mmapOfGenreCheckouts.insert( {genre,iBookID} );

//            cout<<"In Recommend: \""<<pBook->getTitle()<<"\" by "<<pBook->getAuthor()<<" ["<<pBook->getGenre()<<"] (BookID# "<<iBookID<<").\n";
        }
    } // end of for loop for pHistory


    string str_prev="", str_next="";
    multimap<string, int>::iterator itr1, itr2;
    pair <multimap<string,int>::iterator, multimap<string,int>::iterator> ret;

    multimap<int,string> mmapOfCountAuthor;
    itr1=mmapOfAuthorCheckouts.begin();
    if (itr1 != mmapOfAuthorCheckouts.end()) {
        str_prev=itr1->first;
        for (; itr1 != mmapOfAuthorCheckouts.end(); itr1++) {
            str_next=itr1->first;
            if (str_prev.compare(str_next)!=0 ) {
                int count=0;
                //getting a new range of keys
                ret = mmapOfAuthorCheckouts.equal_range(str_prev);
                for (itr2=ret.first; itr2 != ret.second; itr2++) {
                    count++;
                }
                //count reprsent the frequency a given author appears in the checkout list.
//                cout <<"insert to mmapOfCountAuthor: count="<<count<<"; author="<<str_prev<<"\n";
                mmapOfCountAuthor.insert( {count, str_prev} );
                str_prev=str_next;
            }
        }
        int count=0;
        //getting a new range of keys
        ret = mmapOfAuthorCheckouts.equal_range(str_next);
        for (itr2=ret.first; itr2 != ret.second; itr2++) {
            count++;
        }
        //count reprsent the frequency a given author appears in the checkout list.
//        cout <<"insert to mmapOfCountAuthor: count="<<count<<"; author="<<str_next<<"\n";
        mmapOfCountAuthor.insert( {count, str_next} );
    }
    string mostReadAuthor="";
    multimap<int, string>::reverse_iterator ritr1;
    ritr1=mmapOfCountAuthor.rbegin();
    if (ritr1 != mmapOfCountAuthor.rend()) {
        //the author with the highest frequency of count is the most read author.
        mostReadAuthor=ritr1->second;
    }
//    cout <<"The most read author: "<<mostReadAuthor<<"\n";

    multimap<int,string> mmapOfCountGenre;
    itr1=mmapOfGenreCheckouts.begin();
    if (itr1 != mmapOfGenreCheckouts.end()) {
        str_prev=itr1->first;
        for (; itr1 != mmapOfGenreCheckouts.end(); itr1++) {
            str_next=itr1->first;
            if (str_prev.compare(str_next)!=0 ) {
                int count=0;
                //getting a new range of keys
                ret = mmapOfGenreCheckouts.equal_range(str_prev);
                for (itr2=ret.first; itr2 != ret.second; itr2++) {
                    count++;
                }
                //count reprsent the frequency a given genre appears in the checkout list.
//                cout <<"insert to mmapOfCountGenre: count="<<count<<"; genre="<<str_prev<<"\n";
                mmapOfCountGenre.insert( {count, str_prev} );
                str_prev=str_next;
            }
        }
        int count=0;
        //getting a new range of keys
        ret = mmapOfGenreCheckouts.equal_range(str_next);
        for (itr2=ret.first; itr2 != ret.second; itr2++) {
            count++;
        }
        //count reprsent the frequency a given genre appears in the checkout list.
//        cout <<"insert to mmapOfCountGenre: count="<<count<<"; genre="<<str_next<<"\n";
        mmapOfCountGenre.insert( {count, str_next} );
    }
    string mostReadGenre1="",mostReadGenre2="";
    ritr1=mmapOfCountGenre.rbegin();
    if (ritr1 != mmapOfCountGenre.rend()) {
        //the genre with the highest frequency of count is the most read genre1.
        mostReadGenre1=ritr1->second;

        ritr1++;
        if (ritr1 != mmapOfCountGenre.rend())
            mostReadGenre2=ritr1->second;
    }
//    cout <<"The most read genre1: "<<mostReadGenre1<<"\n";
//    cout <<"The most read genre2: "<<mostReadGenre2<<"\n";



    //Now that we have the info on most read author, mostReadAuthor, and  most read genres: mostReadGenre1 and mostReadGenre2,
    //we want to get the recommended books for this account.
    multimap<string, int>::iterator itrGenre1, itrGenre2;
    pair <multimap<string,int>::iterator, multimap<string,int>::iterator> retGenre;
    multimap<string,int> MyMmapOfGenre=bookMgr->getMmapOfGenre();

    multimap<int,int> mmapOfGenre1PopScore;
    retGenre = MyMmapOfGenre.equal_range(mostReadGenre1);
    for (itrGenre1=retGenre.first; itrGenre1 != retGenre.second; itrGenre1++) {
        Book* pBook=bookMgr->getABook(itrGenre1->second);
//        cout<<"MostReadGenre1:"<<mostReadGenre1<<"; popscore: "<<pBook->getPopScore()<<"; bookID: "<<pBook->getBookID()<<"\n";
        mmapOfGenre1PopScore.insert( {pBook->getPopScore(),pBook->getBookID()} );
    }
    multimap<int,int> mmapOfGenre2PopScore;
    retGenre = MyMmapOfGenre.equal_range(mostReadGenre2);
    for (itrGenre1=retGenre.first; itrGenre1 != retGenre.second; itrGenre1++) {
        Book* pBook=bookMgr->getABook(itrGenre1->second);
//        cout<<"MostReadGenre2:"<<mostReadGenre2<<"; popscore: "<<pBook->getPopScore()<<"; bookID: "<<pBook->getBookID()<<"\n";
        mmapOfGenre2PopScore.insert( {pBook->getPopScore(),pBook->getBookID()} );
    }

    int tmpId=0,G1BookId1=0,G1BookId2=0,G2BookId1=0, G2BookId2=0;
    bool bFound1=false, bFound2=false;
    multimap<int, int>::reverse_iterator ritrPopScore1, ritrPopScore2;
    for (ritrPopScore1=mmapOfGenre1PopScore.rbegin(); ritrPopScore1 != mmapOfGenre1PopScore.rend(); ritrPopScore1++) {
        //the bookid with the highest pop score is the recommended book.
        tmpId=ritrPopScore1->second;
//        cout <<"tmpID: "<<tmpId<<"\n";
        if (pHistory->find(tmpId) == pHistory->end()) {
            // This bookId is not in checkoutHistory, so it hasn't been read by the user yet.
            if (!bFound1) {
                G1BookId1=tmpId;
                bFound1=true;
//                cout<<"Found G1BookId1: "<<G1BookId1<<"\n";
            } else if (!bFound2) {
                G1BookId2=tmpId;
                bFound2=true;
//                cout<<"Found G1BookId2: "<<G1BookId2<<"\n";
            }
        }
    }
    bFound1=false;
    bFound2=false;
    for (ritrPopScore2=mmapOfGenre2PopScore.rbegin(); ritrPopScore2 != mmapOfGenre2PopScore.rend(); ritrPopScore2++) {
        //the bookid with the highest pop score is the recommended book.
        tmpId=ritrPopScore2->second;
//        cout <<"tmpID: "<<tmpId<<"\n";
        if (pHistory->find(tmpId) == pHistory->end()) {
            // This bookId is not in checkoutHistory, so it hasn't been read by the user yet.
            if (!bFound1) {
                G2BookId1=tmpId;
                bFound1=true;
//                cout<<"Found G2BookId1: "<<G2BookId1<<"\n";
            } else if (!bFound2) {
                G2BookId2=tmpId;
                bFound2=true;
//                cout<<"Found G2BookId2: "<<G2BookId2<<"\n";
            }
        }
    }


    multimap<string, int>::iterator itrAuthor;
    pair <multimap<string,int>::iterator, multimap<string,int>::iterator> retAuthor;

    multimap<string,int> MyMmapOfAuthor=bookMgr->getMmapOfAuthor();
    multimap<int,int> mmapOfAuthorPopScore;
    retAuthor = MyMmapOfAuthor.equal_range(mostReadAuthor);
    for (itrAuthor=retAuthor.first; itrAuthor != retAuthor.second; itrAuthor++) {
        Book* pBook=bookMgr->getABook(itrAuthor->second);
//        cout<<"mostReadAuthor:"<<mostReadAuthor<<"; popscore: "<<pBook->getPopScore()<<"; bookID: "<<pBook->getBookID()<<"\n";
        mmapOfAuthorPopScore.insert( {pBook->getPopScore(),pBook->getBookID()} );
    }
    int mostReadAuthorId=0;
    bool bFound=false;
    multimap<int, int>::reverse_iterator ritrAuthorPopScore;
    for (ritrAuthorPopScore=mmapOfAuthorPopScore.rbegin(); ritrAuthorPopScore != mmapOfAuthorPopScore.rend(); ritrAuthorPopScore++) {
        //the bookid with the highest pop score is the recommended book.
        tmpId=ritrAuthorPopScore->second;
//        cout <<"tmpID: "<<tmpId<<"\n";
        if ( (pHistory->find(tmpId) == pHistory->end()) && (tmpId != G1BookId1) && (tmpId != G1BookId2) && (tmpId != G2BookId1) && (tmpId != G2BookId2)  )  {
            // This bookId is not in checkoutHistory, so it hasn't been read by the user yet.
            // This bookId also is not the same as one of the 4 chosen books for the two most read genres.
            if (!bFound) {
                mostReadAuthorId=tmpId;
                bFound=true;
//                cout<<"Found mostReadAuthorId: "<<mostReadAuthorId<<"\n";
            }
        }
    }

    //print out the recommended books.
    if ( (G1BookId1 ==0) && (G1BookId2 ==0) && (G2BookId1 ==0) && (G2BookId2 ==0) && (mostReadAuthorId ==0) ) {
        cout <<"No available recommendations.\n";
    } else {
        if ( (mostReadGenre1 != "") && ((G1BookId1>0) || (G1BookId2>0)) ){
            cout <<"You love "<<mostReadGenre1<<". We recommend:\n";
            printRecommendedBooks(G1BookId1,1);
            printRecommendedBooks(G1BookId2,2);
        }
        if ( (mostReadGenre2 != "") && ((G2BookId1>0) || (G2BookId2>0)) ){
            cout <<"You love "<<mostReadGenre2<<". We recommend:\n";
            printRecommendedBooks(G2BookId1,1);
            printRecommendedBooks(G2BookId2,2);
        }
        if ( (mostReadAuthor != "") && (mostReadAuthorId >0) ) {
            cout <<"You love "<<mostReadAuthor<<". We recommend:\n";
            printRecommendedBooks(mostReadAuthorId,2);
        }
    }
    return true;
}

void Library::printRecommendedBooks(int bookID, int pos) {
    Book* pBook = bookMgr->getABook(bookID);
    if (pBook) {
        cout<<pos<<".  \""<<pBook->getTitle()<<"\" by "<<pBook->getAuthor()<<" (BookID# "<<pBook->getBookID()<<") ["<<pBook->getGenre()<<"]. ";
        if (pBook->getIsCheckedOut()){
            cout<<"CHECKED OUT (AccountID# "<<pBook->getAcctID()<<").\n";
        } else {
            cout <<"AVAILABLE\n";
        }
    }
}

bool Library::addABook(string title,string author,string genre) {
    bookMgr->addABook(title,author,genre);
    return true;
}

bool Library::removeABook(int bookID) {
    if (bookMgr->isBookMgrEmpty()) {
        cout<<"No books in your library.\n";
        return false;
    }

    Book* pBook = bookMgr->getABook(bookID);
    if (!pBook) {
        cout << "BookID# " << bookID << " not found.\n";
        return false;
    }

    if (pBook->getIsCheckedOut() == true) {
        // if this book is checked, we first need to clean up the account that checked out this book.
        int accountID =pBook->getAcctID();
        Account* pAcct = acctMgr->getAnAccount(accountID);
        if (!pAcct) {
            cout << "AccountID# " << accountID << " not found.\n";
            return false;
        }
        cout <<"Force returning bok from AccountID# "<<accountID<<"\n";

        set<int>* psetCheckOut=pAcct->getCheckedOutBooks();
        //Delete the BookID from the set of Checked out books for this account.
        psetCheckOut->erase(bookID);

        //decrement the number of checked out by 1 for this account.
        int iNumCheckedOut=pAcct->getNumCheckedOut();
        pAcct->setNumCheckedOut(iNumCheckedOut-1);

        //update account manager's multimap "mmapOfCheckout" to reflect the change in the number of checkout.
        acctMgr->UpdatemmapOfCheckout(accountID,iNumCheckedOut,iNumCheckedOut-1);
    } // end of if book is checked out.

    //remove this book from map,set,and multimap indices from the book manager.
    bookMgr->removeABook(bookID);
    cout <<"\""<<pBook->getTitle()<<"\" by "<<pBook->getAuthor()<<" successfully removed.\n";

    //deallocate the memory for the book object.
    delete pBook;

    return true;
}

bool Library::addAnAcct(string userName) {
    if (userName != "") {
        acctMgr->addAnAcct(userName);
        return true;
    } else
        return false;
}

bool Library::removeAnAcct(int acctID) {
    if (acctMgr->isAcctMgrEmpty()) {
        cout<<"No accounts in your library.\n";
        return false;
    }

    Account* pAcct = acctMgr->getAnAccount(acctID);
    if (!pAcct) {
        cout << "AccountID# " << acctID << " not found.\n";
        return false;
    }

    int numCheckOut = pAcct->getNumCheckedOut();
    set<int> *psetCheckedOutBooks = pAcct->getCheckedOutBooks();
    // Iterate over the set using Iterator
    set<int>::iterator itr;

    if ( numCheckOut > 0 ) {
        for (itr=psetCheckedOutBooks->begin(); itr!=psetCheckedOutBooks->end(); ++itr) {
            int iBookID = *itr;
            Book *pBook = bookMgr->getABook(iBookID);
            if (pBook) {
                pBook->setIsCheckedOut(false);
                cout<<"\""<<pBook->getTitle()<<"\" by "<<pBook->getAuthor()<<" (BookID# "<<iBookID<<") force returned.\n";
            }
        } // end of for loop for psetCheckedOutBooks
    } // end of if numCheckOut > 0

    //Delete all elements from the set of Checked out books for this account.
    psetCheckedOutBooks->erase(psetCheckedOutBooks->begin(),psetCheckedOutBooks->end());

    //Delete all elements from the set of Checked out books history for this account.
    set<int> *psetCheckedOutBooksHistory = pAcct->getCheckedOutBooksHistory();
    psetCheckedOutBooksHistory->erase(psetCheckedOutBooksHistory->begin(),psetCheckedOutBooksHistory->end());

    //remove this account from map,set,and multimap indices from the account manager.
    acctMgr->removeAnAcct(acctID);
    cout <<pAcct->getUserName()<<"'s account successfully removed.\n";

    //deallocate the memory for the set objects for the account.
    delete psetCheckedOutBooks;
    delete psetCheckedOutBooksHistory;
    //deallocate the memory for the account object.
    delete pAcct;

    return true;
}

bool Library::systemInfo() {
    int numOfBooks=0;
    int numOfBooksOverdue=0;
    int numOfAccounts=0;
    int numofAccountsOverdue=0;

    numOfBooks=bookMgr->getTotalNumBooks();
    numOfBooksOverdue=bookMgr->getTotalNumBooksOverdue();
    numOfAccounts=acctMgr->getTotalNumAccounts();
    numofAccountsOverdue=acctMgr->getTotalNumAccountsOverdue();

    cout<<"System time: "<<Time::getTime()<<"\n";
    cout<<"Number of books: "<<numOfBooks<<"\n";
    cout<<"Number of overdue books: "<<numOfBooksOverdue<<"\n";
    cout<<"Number of accounts: "<<numOfAccounts<<"\n";
    cout<<"Number of overdue accounts: "<<numofAccountsOverdue<<"\n";

    return true;
}

void Library::timeTravel(unsigned int uiTravel) {
    unsigned int oldTime = Time::getTime();
    Time::timeTravel(uiTravel);
    cout << "Travelled "<<uiTravel<<" days through time ("<<oldTime<<" --> "<<Time::getTime()<<").\n";
}

bool Library::exportToBookfile(string bookFilename) {
    ofstream outFile;

    outFile.open(bookFilename);
    if (!outFile.is_open()) {
        cout << "Unable to open file: "<<bookFilename<<"\n";
        return false;
    }

    unordered_map<int,Book*> myUmapBook=bookMgr->getUmapBook();
    int numOfBooks=myUmapBook.size();
    outFile <<numOfBooks<<"\n";

    Book* pBook= NULL;
    unordered_map<int, Book*>::const_iterator itrBk;
    for (itrBk=myUmapBook.begin(); itrBk != myUmapBook.end(); ++itrBk) {
        pBook=itrBk->second;
        outFile<<pBook->getBookID()<<"|"<<pBook->getTitle()<<"|"<<pBook->getAuthor()<<"|"<<pBook->getGenre()<<"|"<<pBook->getPopScore()<<"\n";
    }

    cout <<"Books data successfully exported to \""<<bookFilename<<"\"\n";
    outFile.close();
    return true;
}

bool Library::exportToAcctfile(string acctFilename) {
    ofstream outFile;

    outFile.open(acctFilename);
    if (!outFile.is_open()) {
        cout << "Unable to open file: "<<acctFilename<<"\n";
        return false;
    }

    unordered_map<int,Account*> myUmapAcct=acctMgr->getUmapAccount();
    int numOfAccts=myUmapAcct.size();
    outFile <<numOfAccts<<"\n";

    Account* pAcct= NULL;
    unordered_map<int, Account*>::const_iterator itrAcct;
    for (itrAcct=myUmapAcct.begin(); itrAcct != myUmapAcct.end(); ++itrAcct) {
        pAcct=itrAcct->second;
        outFile<<pAcct->getAccountID()<<"|"<<pAcct->getUserName()<<"|"<<pAcct->getNumCheckedOut()<<"\n";

        set<int>* myCheckedOutBooks=pAcct->getCheckedOutBooks();
        // Iterate over the set using Iterator
        set<int>::iterator itr;
        for (itr=myCheckedOutBooks->begin(); itr!=myCheckedOutBooks->end(); ++itr) {
            int iBookID = *itr;
            Book *pBook = bookMgr->getABook(iBookID);
            if (pBook) {
                string author = pBook->getAuthor();
                string genre = pBook->getGenre();
                outFile << pBook->getBookID() << "|" << pBook->getDueDate() << "|" << pBook->getRenewals() << "\n";
            }
        } // for loop for checkedout books in myCheckedOutBooks for this account.
    } // for loop for the account in myUmapAcct.

    cout <<"Accounts data successfully exported to \""<<acctFilename<<"\"\n";
    outFile.close();
    return true;
}

void Library::exportToFiles(string bookFilename,string acctFilename) {
    exportToBookfile(bookFilename);
    exportToAcctfile(acctFilename);
}


void Library::displayHelpMsg () {
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

void Library::displayExitMsg() {
    cout <<"Thank you for using StackOverdue!\n\n";
}
