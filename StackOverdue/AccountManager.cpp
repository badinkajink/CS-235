//
// Created by WilliamUSER on 12/9/2017.
//

#include <iomanip>
#include <fstream>
#include <iostream>
#include <stack>

//unordered_map
#include <bits/stdc++.h>

#include "BookManager.h"

#include "Time.h"
#include "Account.h"
#include "AccountFileReader.h"
#include "AccountManager.h"

bool AccountManager::loadAccounts(string sAcctFileName) {
    AccountFileReader acctReader;

    acctReader.readAccountFile(umapAccount,sAcctFileName, pBookMgr);

//  acctReader.printAccountFile(umapAccount, pBookMgr);

    createAcctIndices();

    return true;
}

void AccountManager::createAcctIndices() {
    int iAcctID;
    string sUserName;
    int iNumCheckedOut;

//    cout <<"\n\n In AccountManager CreateIndices\n";
    unordered_map<int , Account*>:: iterator itrAcct;
    for (itrAcct = umapAccount.begin(); itrAcct != umapAccount.end(); itrAcct++)
    {
        Account* pTmpAccount = itrAcct->second;

        iAcctID=pTmpAccount->getAccountID();
        sUserName=pTmpAccount->getUserName();
        iNumCheckedOut=pTmpAccount->getNumCheckedOut();

        setAcctID.insert(iAcctID);
        mmapOfAcctName.insert( {sUserName,iAcctID} );
        mmapOfCheckout.insert( {iNumCheckedOut,iAcctID} );
    } // for loop itrAcct

}

bool AccountManager::isAcctMgrEmpty() {
    if (setAcctID.empty()) {
        return true;
    } else {
        return false;
    }
}

void AccountManager::browseAccountsByName() {
    int count=1;
    // Iterate over the multimap using Iterator
    multimap<string, int>::iterator itr;
    for (itr = mmapOfAcctName.begin(); itr != mmapOfAcctName.end(); itr++) {
        int iAcctID = itr->second;
        Account* pTmpAcct=getAnAccount(iAcctID);

        if (pTmpAcct) {
            cout <<count<<". "<<pTmpAcct->getUserName()<<" (AccountID# "<<pTmpAcct->getAccountID()<<"). ";
            if (pTmpAcct->getNumCheckedOut()==0) {
                cout <<"No books checked out.\n";
            } else if (pTmpAcct->getNumCheckedOut() >0 ){
                cout <<pTmpAcct->getNumCheckedOut()<<" books checked out:\n";

                set<int> *psetCheckedOutBooks = pTmpAcct->getCheckedOutBooks();
                int iBookID;
                int cnt=1;
                // Iterate over the set using Iterator
                set<int>::iterator itr;
                for (itr=psetCheckedOutBooks->begin(); itr!=psetCheckedOutBooks->end(); ++itr) {
                    iBookID = *itr;
                    Book *pBook = pBookMgr->getABook(iBookID);
                    if (pBook) {
                        cout <<"        "<<cnt<<". \""<<pBook->getTitle()<<"\" by "<<pBook->getAuthor()<<" (BookID# "<<pBook->getBookID()<<") ["<<pBook->getGenre()<<"]. \n";
                    } else {
                        cout << "BookID# " << iBookID << " not found.\n";
                    }
                    cnt++;
                } // end of for loop for psetCheckedOutBooks
            } // end of else if pTmpAcct->getNumCheckedOut
            count++;
        } // enf of if pTmpAcct
    } // end of for loop for mmapOfAcctName
}

void AccountManager::browseAccountsByAccountid() {
    int count=1;
    // Iterate over the set using Iterator
    set<int>::iterator itr;
    for (itr=setAcctID.begin(); itr!=setAcctID.end(); ++itr) {
        int iAcctID = *itr;
        Account* pTmpAcct=getAnAccount(iAcctID);

        if (pTmpAcct) {
            cout <<count<<". "<<pTmpAcct->getUserName()<<" (AccountID# "<<pTmpAcct->getAccountID()<<"). ";
            if (pTmpAcct->getNumCheckedOut()==0) {
                cout <<"No books checked out.\n";
            } else if (pTmpAcct->getNumCheckedOut() >0 ){
                cout <<pTmpAcct->getNumCheckedOut()<<" books checked out:\n";

                set<int> *psetCheckedOutBooks = pTmpAcct->getCheckedOutBooks();
                int iBookID;
                int cnt=1;
                // Iterate over the set using Iterator
                set<int>::iterator itr;
                for (itr=psetCheckedOutBooks->begin(); itr!=psetCheckedOutBooks->end(); ++itr) {
                    iBookID = *itr;
                    Book *pBook = pBookMgr->getABook(iBookID);
                    if (pBook) {
                        cout <<"        "<<cnt<<". \""<<pBook->getTitle()<<"\" by "<<pBook->getAuthor()<<" (BookID# "<<pBook->getBookID()<<") ["<<pBook->getGenre()<<"]. \n";
                    } else {
                        cout << "BookID# " << iBookID << " not found.\n";
                    }
                    cnt++;
                } // end of for loop for psetCheckedOutBooks
            } // end of else if pTmpAcct->getNumCheckedOut
            count++;
        } // enf of if pTmpAcct
    } // end of for loop for setAcctID
}

// Number of checked out books ordering is descending.  The reverse iterator is used to accomplished that.
void AccountManager::browseAccountsByCheckouts() {
    int count=1;
    // Iterate over the multimap using Iterator
    multimap<int, int>::reverse_iterator ritr;
    for (ritr = mmapOfCheckout.rbegin(); ritr != mmapOfCheckout.rend(); ritr++) {
        int iAcctID = ritr->second;
        Account* pTmpAcct=getAnAccount(iAcctID);

        if (pTmpAcct) {
            cout <<count<<". "<<pTmpAcct->getUserName()<<" (AccountID# "<<pTmpAcct->getAccountID()<<"). ";
            if (pTmpAcct->getNumCheckedOut()==0) {
                cout <<"No books checked out.\n";
            } else if (pTmpAcct->getNumCheckedOut() >0 ){
                cout <<pTmpAcct->getNumCheckedOut()<<" books checked out:\n";

/*
                vector<int> *vCheckedOutBooks = pTmpAcct->getCheckedOutBooks();
                int iBookID;
                for (unsigned int i = 0; i < vCheckedOutBooks->size(); i++) {
                    iBookID = vCheckedOutBooks->at(i);
                    set<int> *psetCheckedOutBooks = pTmpAcct->getCheckedOutBooks();
                    int iBookID;
*/
                set<int> *psetCheckedOutBooks = pTmpAcct->getCheckedOutBooks();
                int iBookID;
                int cnt=1;
                // Iterate over the set using Iterator
                set<int>::iterator itr;
                for (itr=psetCheckedOutBooks->begin(); itr!=psetCheckedOutBooks->end(); ++itr) {
                    iBookID = *itr;
                    Book *pBook = pBookMgr->getABook(iBookID);
                    if (pBook) {
                        cout <<"        "<<cnt<<". \""<<pBook->getTitle()<<"\" by "<<pBook->getAuthor()<<" (BookID# "<<pBook->getBookID()<<") ["<<pBook->getGenre()<<"]. \n";
                    } else {
                        cout << "BookID# " << iBookID << " not found.\n";
                    }
                    cnt++;
                } // end of for loop for psetCheckedOutBooks
            } // end of else if pTmpAcct->getNumCheckedOut
            count++;
        } // enf of if pTmpAcct
    } // end of for loop for mmapOfCheckout
}

// Return the pointer to the account for a found AcctID.  If not found, a NULL pointer will be returned.
Account* AccountManager::getAnAccount(int iAcctID) {
    Account* pAcct= NULL;

    unordered_map<int, Account*>::const_iterator itrAcct = umapAccount.find (iAcctID);
    if ( itrAcct != umapAccount.end() ) {
        pAcct = itrAcct->second;
    }

    return pAcct;
}

int AccountManager::getTotalNumAccounts() {
    return setAcctID.size();
}

int AccountManager::getTotalNumAccountsOverdue() {
    int numAccountOverdue=0;

    // Iterate over the set using Iterator
    set<int>::iterator itr;
    for (itr=setAcctID.begin(); itr!=setAcctID.end(); ++itr) {
        int iAcctID = *itr;
        if (updateOverdue(iAcctID) > 0)
            numAccountOverdue++;
    }
    return numAccountOverdue;
}

//count the number of checked out books that are overdue for a given account.
int AccountManager::updateOverdue(int acctID) {
    int iBookID;
    int iOverdue = 0;
    Account* pAcct = getAnAccount(acctID);
    if (pAcct) {
        set<int> *psetCheckedOutBooks = pAcct->getCheckedOutBooks();

        // Iterate over the set using Iterator
        set<int>::iterator itr;
        for (itr=psetCheckedOutBooks->begin(); itr!=psetCheckedOutBooks->end(); ++itr) {
            iBookID = *itr;
            Book *pBook = pBookMgr->getABook(iBookID);
            if (pBook) {
                if (Time::getTime() > (unsigned int) pBook->getDueDate())
                    iOverdue++;
            }
        } // for loop to count the number of overdue books.
        pAcct->setOverdue(iOverdue);
    }
    return iOverdue;
}

//Remove the entry from mmapOfAcctName that has (userName, acctID)
void AccountManager::DeleteEntryInmmapOfAcctName (string userName,int acctID) {
    bool bFound=false;
    multimap<string, int>::iterator itr, save_it;
    for (itr = mmapOfAcctName.begin(); itr != mmapOfAcctName.end(); itr++) {
        if ( (itr->first.compare(userName) == 0) && (itr->second == acctID) ) {
            save_it = itr;
            bFound=true;
        }
    }
    //remove the old entry at the iterator position from the multimap "mmapOfAcctName".
    if (bFound)
        mmapOfAcctName.erase(save_it);
}

//Remove the entry from mmapOfCheckout that has (oldCheckoutVal, acctID)
void AccountManager::DeleteEntryInmmapOfCheckout (int oldCheckoutVal, int acctID ) {
    bool bFound=false;
    multimap<int, int>::iterator itr, save_it;
    for (itr = mmapOfCheckout.begin(); itr != mmapOfCheckout.end(); itr++) {
        if ( (itr->first == oldCheckoutVal) && (itr->second == acctID) ) {
            save_it = itr;
            bFound=true;
        }
    }
    //remove the old entry at the iterator position from the multimap "mmapOfCheckout".
    if (bFound)
        mmapOfCheckout.erase(save_it);
}

//update account manager's multimap "mmapOfCheckout" to reflect the change in the number of checkout.
//Remove the mmap entry (oldCheckoutVal, acctID)
//then add the mmap entry (newCheckoutVal, acctID)
void AccountManager::UpdatemmapOfCheckout (int acctID, int oldCheckoutVal, int newCheckoutVal) {

    //remove the old entry at the iterator position from the multimap "mmapOfCheckout".
    DeleteEntryInmmapOfCheckout(oldCheckoutVal,acctID);
    //insert the entry to the multimap "mmapOfCheckout".
    mmapOfCheckout.insert( {newCheckoutVal,acctID});
}

bool AccountManager::addAnAcct(string userName) {
    if (userName == "")
        return false;

    int newAcctID = 1;
    if (!setAcctID.empty()) {
        // Since the set is ordered. The last element of the set for the AccountManager has the largest value.
        // set the new Account ID to be the current largest Account ID + 1.
        newAcctID = *setAcctID.rbegin() + 1;
    }

    //create the set objects for both Checkedout and checkedout history.
    set<int> *pCheckedOut=new set<int>;
    set<int> *pBookHistory=new set<int>;

    //create the Account object.
    Account* pAccount = new Account(newAcctID,userName,0);
    pAccount->setCheckedOutBooks(pCheckedOut);
    pAccount->setCheckedOutBooksHistory(pBookHistory);

    //insert the account pointer to the unordered map "umapAccount".
    umapAccount.insert( { newAcctID,pAccount });
    //insert the new account ID to set "setAcctID".
    setAcctID.insert(newAcctID);
    //insert the user name to the multimap "mmapOfAcctName".
    mmapOfAcctName.insert( {userName,newAcctID} );
    mmapOfCheckout.insert( {0,newAcctID});

    cout<<"AccountID# "<<newAcctID<<" successfully created.\n";
    return true;
}

bool AccountManager::removeAnAcct(int acctID) {

    Account* pAcct = getAnAccount(acctID);
    //remove the old entry at the iterator position from the multimap "mmapOfCheckout".
    DeleteEntryInmmapOfCheckout(pAcct->getNumCheckedOut(),acctID);

    //remove the old entry at the iterator position from the multimap "mmapOfAcctName".
    DeleteEntryInmmapOfAcctName(pAcct->getUserName(),acctID);

    umapAccount.erase(acctID);
    setAcctID.erase(acctID);

    return true;
}