## Solution - Flashcards

Static arrays in C++ pose a very common problem-the need to know exactly how big the array should be at compile time. Frequently, we do not know this information because the values come from a variable input source, such as a file of unknown size or keyboard user input. Dynamic arrays solve this problem by allowing the number of values stored to be determined at run time.

A vector serves as a wrapper for a dynamic array-a wrapper in that it surrounds the array with a class, creating an interface that provides certain functionality, such as accessing, removing, or counting the underlying elements. A further benefit is that vectors handle the dynamic memory allocation and resizing of arrays as necessary under the hood.

This code implements the UniqueVector class, a specialized vector that maintains a condition of unique-ness--that is to say, it does not contain any duplicates. Moreover, a UniqueVector is used inside of a FlashcardDeck class to maintain a deck of Flashcards.

## Compiling and Executing

The main program sequence essentially runs tests to ensure valid functionality for both `UniqueVector` and `FlashcardDeck`. To compile and execute the code, run:

```
$ make
$ ./UniqueVector
```

## Class Functionality

**The UniqueVector class interface provides the following functionality:**

1.	`unsigned int capacity()` - Returns the size of the space currently allocated for the vector.

2.	`unsigned int size()` - Returns the current number of elements in the vector.

3.	`bool empty()` - If the vector contains zero elements, returns true; otherwise, returns false.

4.	`bool contains(const T& data)` - If the vector contains data, returns true; otherwise, returns false.

5.	`bool at(unsigned int pos, T& data)` - If pos is a valid position, retrieves the element in position pos in the array, stores it in data, and returns true; otherwise, returns false.

6.	`bool insert(const T& data)` - If the vector does not already contain data, adds a new element, data, to the back of the vector, increases the container size by one, and returns true; otherwise, returns false. If the underlying array is full, creates a new array with double the capacity and copies all of the elements over.

7.	`bool insert(const T& data, unsigned int pos)` - If the vector does not already contain data, adds a new element, data, to the vector at position pos, increases the container size by one, returns true; otherwise, returns false. If the underlying array is full, creates a new array with double the capacity and copies all of the elements over.

8.	`bool push_front(const T& data)` - If the vector does not already contain data, adds a new element, data, to the front of the vector, increases the container size by one, and returns true; otherwise, returns false. If the underlying array is full, creates a new array with double the capacity and copies all of the elements over.

9.	`bool remove(const T& data)` - If the vector contains data, removes data from the vector, reduces the container size by one, leaves the capacity unchanged, and returns true; otherwise, returns false.

10.	`bool remove(unsigned int pos, T& data)` - If pos is a valid position, removes the element in position pos, stores it in data, reduces the container size by one, leaves the capacity unchanged, and returns true; otherwise, returns false.

11.	`bool pop_back(T& data)` - If the vector is not empty, removes the last element in the vector, stores it in data, reduces the container size by one, leaves the capacity unchanged, and returns true; otherwise, returns false.

12.	`void clear()` - Empties the vector of its elements and resets the capacity to 3.

13.	Overload `operator==` - If the vector on the left hand side has the same elements in the same order as the vector on the right hand side, returns true; otherwise, returns false.

**The Flashcard interface provides the following functionality:**

1.	Overload `operator==` — If the flashcard on the left hand side has the same front value as the flashcard on the right hand side, return true; otherwise, return false.

2. 	Overload `operator<<` - Outputs flashcard in the format first showing the front, followed by a newline, followed by back, followed by two newlines.

**The FlashcardDeck class interface provides the following functionality:** _(Note that the extra credit is completed)_

1.	`bool addCard(const string& front, const string& back)` — If a card with the same front is not already in the pack, adds a new card with the supplied front and back and return true; otherwise, returns false.
2.	`bool removeCard(const string& front)` — If a card with the provided front is in the pack, remove the card from the pack and return true; otherwise, returns false.
3.	`bool containsCard(const string& front)` — If a card with the provided front is in the pack, return true; otherwise, return false.
4.	`string listFlashcards()` — Return a string containing all of the Flashcards, showing a front value, followed by a newline, followed by the respective back value, followed by two newlines.

5.	`void combineFlashcards(FlashcardDeck& otherFlashcardDeck)`  — Any Flashcards in otherFlashcards that do not exist in this FlashcardDeck are added to this.

6. 	`void shuffleFlashcards(FlashcardDeck& otherFlashcardDeck)` - Combine the Flashcards in this with the Flashcards in otherFlashcards in such an order that the first Flashcard in this is followed by the first Flashcard in otherFlashcardDeck that does not exist in this, followed by the second Flashcard in this, then the second Flashcard in otherFlashcardDeck that does not exist in this, etc, and add all remaining to the end.
