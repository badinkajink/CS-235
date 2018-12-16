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
#include "BookManager.h"
#include "Account.h"
#include "AccountFileReader.h"

using namespace std; // make std members visible

struct field_reader: std::ctype<char> {

    field_reader(): std::ctype<char>(get_table()) {}

    static std::ctype_base::mask const* get_table() {
        static std::vector<std::ctype_base::mask>
                rc(table_size, std::ctype_base::mask());

        rc['|'] = std::ctype_base::space;
        return &rc[0];
    }
};

bool AccountFileReader::readAccountFile(unordered_map<int, Account*> &umapAccount, string sAccountFileName, BookManager* pBookMgr) {
    ifstream inFile;
    int count;
    string line;

    int iAcctID;
    string sUserName;
    int iNumCheckedOut;

    if (sAccountFileName== "") {
        cout << "No accounts provided.\n";
        return 1;
    }

    inFile.open(sAccountFileName);
    if (!inFile) {
        cout << "Could not find file \""<<sAccountFileName<<"\". Skipping.\n";
        return 1;
    } else {
        cout << "Loading accounts from \""<<sAccountFileName<<"\".\n";
    }

    inFile >> count;
//    cout << "The total num of accounts: " << count << "\n";
    // get rid of the "\n" character
    getline(inFile,line);

    for (int i = 0; i < count; i++) {
        // Read the next line in the book file.
        getline(inFile,line);

        stringstream input (line);
        // have the stream use our ctype facet:
        input.imbue(std::locale(std::locale(), new field_reader()));

        input >> iAcctID;
        input >> sUserName;
        input >> iNumCheckedOut;
//        cout <<"Account ID: "<<iAcctID<<"; UserName: "<<sUserName<<"; Number of Checked out books: "<<iNumCheckedOut<<".\n";

        set<int> *pCheckedOut=new set<int>;
        set<int> *pBookHistory=new set<int>;

        int iBookID;
        int iDueDate;
        int iRenewals;
        if (iNumCheckedOut > 0) {
            for (int j=0; j<iNumCheckedOut; j++){
                getline(inFile,line);

                stringstream input (line);
                // have the stream use our ctype facet:
                input.imbue(std::locale(std::locale(), new field_reader()));
                input >> iBookID;
                input >> iDueDate;
                input >> iRenewals;
//                cout <<"checkedOut Book ID: "<<iBookID<<"; Due Date: "<<iDueDate<<"; Num of Renewal: "<<iRenewals<<"\n";

                Book* pBook=pBookMgr->getABook(iBookID);
                if (pBook) {
                    pBook->setDueDate(iDueDate);
                    pBook->setRenewals(iRenewals);
                    pBook->setIsCheckedOut(true);
                    pBook->setAcctID(iAcctID);

                    //adding the BookID to the set of Checked out books for this account.
                    pCheckedOut->insert(iBookID);
                    //adding the BookID to the set of Checked out books history for this account.
                    pBookHistory->insert(iBookID);
                } else {
                    cout << "Could not find library book with ID# "<<iBookID<<".\n";
                }
            } // for loop for iNumCheckedOut
        } // if iNumCheckedOut >0

        Account* pAccount = new Account(iAcctID,sUserName,iNumCheckedOut);
        pAccount->setCheckedOutBooks(pCheckedOut);
        pAccount->setCheckedOutBooksHistory(pBookHistory);

        umapAccount.insert( { iAcctID,pAccount });
    }
    inFile.close();

    return 0;
}

int AccountFileReader::printAccountFile(unordered_map<int, Account*> &umapAccount, BookManager* pBookMgr) {
    int iAcctID;
    string sUserName;
    int iNumCheckedOut;
    int count=1;

    cout << "\n\n\nIn PrintAccountFile\n";

    unordered_map<int , Account*>:: iterator itrAcct;
    for (itrAcct = umapAccount.begin(); itrAcct != umapAccount.end(); itrAcct++)
    {
        Account* pTmpAccount = itrAcct->second;

        iAcctID=pTmpAccount->getAccountID();
        sUserName=pTmpAccount->getUserName();
        iNumCheckedOut=pTmpAccount->getNumCheckedOut();

        cout <<"count= "<<count << "; AccountID: "<<iAcctID<<"; UserName: "<<sUserName<<"; Number of Checked out books: "<<iNumCheckedOut<<".\n";
        count++;

        if (iNumCheckedOut >0) {
/*
            vector <int>* vCheckedOut = pTmpAccount->getCheckedOutBooks();
            for (unsigned int j=0; j<vCheckedOut->size(); j++){
                int iBookID=vCheckedOut->at(j);
*/

            set<int> *psetCheckedOutBooks = pTmpAccount->getCheckedOutBooks();
            int iBookID;
            // Iterate over the set using Iterator
            set<int>::iterator itr;
            for (itr=psetCheckedOutBooks->begin(); itr!=psetCheckedOutBooks->end(); ++itr) {
                iBookID = *itr;
                Book *pBook = pBookMgr->getABook(iBookID);
//                cout <<"The checked out Book ID:"<<iBookID<<"\n";
                if (pBook) {
                    int iTmpBookID = pBook->getBookID();
                    int iDueDate = pBook->getDueDate();
                    int iRenewals=pBook->getRenewals();
                    int iTmpAcctID=pBook->getAcctID();
                    string sTitle = pBook->getTitle();

                    cout <<"Book ID: "<<iTmpBookID<<"; iDueDate: "<<iDueDate<<"; Num of Renewal: "<<iRenewals<<"; Title: "<<sTitle<<"; AcctID: "<<iTmpAcctID<<"\n";
                }
            } // for loop for CheckedOut books
        } // if iNumCheckedOut >0
    } // for loop for itrAcct

    return 0;
}
