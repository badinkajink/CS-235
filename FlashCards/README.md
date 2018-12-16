# Assignment 1 - Flashcards
---

## Description
---
Flashcards are cards with a term on the front and a definition on the back.
Flashcards uses implements three classes, `UniqueVector`, `Flashcard`, and `FlashcardDeck`. 
`FlashcardDeck` contains `Flashcard` objects, which use `UniqueVector` as the underlying data structure.

To adhere to generic programming, I use templating for the UniqueVector class, so that any data types can be passed into functions of the UniqueVector class.

In addition to the provided unit tests, I have my own custom testers in the `main()` function in each class. They are now commented out.

For the sake of efficiency and clarity, I use helper functions wherever I see fit.  For example, <br />
In the UniqueVector class: <br />
I create two helper functions: `isDataFoundInVector` and `doubleCapacity` that are used by `insert` and `push_front` functions. <br />
I also create two helper functions `foundDataToRemove" and `removeDataAtPos` that are used in `remove` function. <br />
I create an additional operator subscript [], since it will be needed by the operator ==. <br />

In the Flashcard class: <br />
I create helper functions `setFront", `setBack`, `getFront`, and `getBack.`

The UniqueVector class can be tested independently by the UniqueVectorTester, before introducing Flashcard and FlashcardDeck classes.

FlashcardDeck use a private variable of object instantiated from the class UniqueVector. The type Flashcard is passed to UniqueVector to hold flashcards in the deck.

