cmake_minimum_required(VERSION 3.7)
project(badinkajink_assignment1_Flashcards)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Flashcard.cpp
        Flashcard.h
        FlashcardDeck.cpp
        FlashcardDeck.h
        UniqueVector.cpp
        UniqueVector.h
)

add_executable(badinkajink_assignment1_Flashcards ${SOURCE_FILES})