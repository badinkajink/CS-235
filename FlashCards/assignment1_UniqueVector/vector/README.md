## Assignment 1 - Flashcards

In order to maximize modularity, I place the interfaces of the classes in separate header files: UniqueVector.h, Flashcard.h, and FlashcardDeck.h.

To adhere to generic programming, I use templating for UniqueVector class, so that any data types can be passed into functions of the UniqueVector class.

In addition to the provided unit tests, I have my own custom testers in the main() function in each class. They are now commented out.

For the sake of efficiency and clarity, I use helper functions wherever I see fit.  For example,
In the UniqueVector class:
I create two helper functions: "isDataFoundInVector" and "doubleCapacity" that are used by "insert" and "push_front" functions.
I also create two helper functions "foundDataToRemove" and "removeDataAtPos" that are used in "remove" function.
I create an additional operator subscript [], since it will be needed by the operator ==.

In the Flashcard class:
I create helper functions "setFront", "setBack", "getFront", and "getBack."

The UniqueVector class can be tested independently by the UniqueVectorTester, before introducing Flashcard and FlashcardDeck classes.

FlashcardDeck use a private variable of object instantiated from the class UniqueVector. The type Flashcard is passed to UniqueVector to hold flashcards in the deck.

