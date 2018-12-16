//
// Created by WilliamUSER on 12/9/2017.
//

#ifndef STACKOVERDUE_BOOKMANAGER_H
#define STACKOVERDUE_BOOKMANAGER_H

#include <iomanip>
#include <fstream>
#include <iostream>

//unordered_map
#include <bits/stdc++.h>
#include <unordered_map>

#include "Book.h"

class BookManager {
private:
    unordered_map<int, Book*> umapBook;
    set<int> setBookID;
    multimap<string,int> mmapOfTitle;
    multimap<string,int> mmapOfAuthor;
    multimap<string,int> mmapOfGenre;
    multimap<int,int> mmapOfPopScore;

public:
    unordered_map<int,Book*> getUmapBook () { return umapBook;}
    multimap<string,int> getMmapOfGenre() { return mmapOfGenre; }
    multimap<string,int> getMmapOfAuthor() { return mmapOfAuthor; }
    bool loadBooks(string sBookFileName);
    void createBookIndices();
    bool isBookMgrEmpty();
    bool isBookExisted(string title,string author);

    void browseBooksByTitle();
    void browseBooksByAuthor();
    void browseBooksByGenre();
    void browseBooksByBookid();
    void browseBooksByPopularity();

    Book* getABook(int iBookID);
    int getTotalNumBooks();
    int getTotalNumBooksOverdue();

    void DeleteEntryInmmapOfTitle (string title,int bookID);
    void DeleteEntryInmmapOfAuthor (string author,int bookID);
    void DeleteEntryInmmapOfGenre (string genre,int bookID);
    void DeleteEntryInmmapOfPopScore (int popscore,int bookID);
    void UpdatemmapOfPopScore (int bookID, int oldPopScore, int newPopScore);

    void searchAllBooks();
    void searchBooksByTitle(string searchWord);
    void searchBooksByAuthor(string searchWord);

    bool addABook(string title,string author,string genre);
    bool removeABook(int bookID);
};


#endif //STACKOVERDUE_BOOKMANAGER_H
