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

bool BookFileReader::readBookFile(unordered_map<int, Book*> &umapBook, string sBookFileName) {
    ifstream inFile;
    int count;
    string word;
    string line;

    int iBookID;
    string sTitle;
    string sAuthor;
    string sGenre;
    int iPopScore;

    if (sBookFileName== "") {
        cout << "No books provided.\n";
        return 1;
    }

    inFile.open(sBookFileName);
    if (!inFile) {
        cout << "Could not find file \""<<sBookFileName<<"\". Skipping.\n";
        return 1;
    } else {
        cout << "Loading books from \""<<sBookFileName<<"\".\n";
    }

    inFile >> count;
//    cout << "The total num of books: " << count << "\n";
    // get rid of the "\n" character
    getline(inFile,line);

    for (int i = 0; i < count; i++) {
        // Read the next line in the book file.
        getline(inFile,line);
//        cout <<"Book input line: "<<line<<"\n";

        stringstream input (line);
        // have the stream use our ctype facet:
        input.imbue(std::locale(std::locale(), new field_reader()));

        input >> iBookID;
        input >> sTitle;
        input >> sAuthor;
        input >> sGenre;
        input >> iPopScore;

//        cout <<"BookID: "<<iBookID<<"; Title: "<<sTitle<<"; Author: "<<sAuthor<<"; Genre: "<<sGenre<<"; PopScore: "<<iPopScore<<".\n";

        Book* pBook = new Book(iBookID,sTitle,sAuthor,sGenre,iPopScore);
        umapBook.insert( { iBookID,pBook });
    }
    inFile.close();

    return 0;
}

int BookFileReader::printBookFile(unordered_map<int, Book*> &umapBook) {
    int iBookID;
    string sTitle;
    string sAuthor;
    string sGenre;
    int iPopScore;
    int count=1;
    cout << "\n\n\nIn PrintBookFile\n";

    unordered_map<int , Book*>:: iterator itrB;
    for (itrB = umapBook.begin(); itrB != umapBook.end(); itrB++)
    {
        Book* pTmpBook = itrB->second;

        iBookID = pTmpBook->getBookID();
        sTitle = pTmpBook->getTitle();
        sAuthor= pTmpBook->getAuthor();
        sGenre= pTmpBook->getGenre();
        iPopScore=pTmpBook->getPopScore();

        cout <<"count= "<<count << "; BookID: "<<iBookID<<"; Title: "<<sTitle<<"; Author: "<<sAuthor<<"; Genre: "<<sGenre<<"; PopScore: "<<iPopScore<<".\n";
        count++;
    }

    return 0;
}
