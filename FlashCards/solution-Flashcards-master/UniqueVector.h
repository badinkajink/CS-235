#ifndef __CS235_UNIQUE_VECTOR_H_
#define __CS235_UNIQUE_VECTOR_H_

#include <iostream>
#include <algorithm>

template<class T>
class UniqueVector {
public:

  /***********************/
  /** Class necessities **/
  /***********************/

 UniqueVector(unsigned int newCapacity = 3) :
  vecSize(0), vecCapacity(newCapacity) { arr = new T[vecCapacity]; }
  ~UniqueVector() { delete[] arr; }

  //copy constructor
  //UniqueVector(const UniqueVector& other);

  /***************************/
  /** Convenience functions **/
  /***************************/

  // Returns the total amount of space currently allocated for the vector
  unsigned int capacity() { return vecCapacity; }

  // Returns the number of elements in the vector
  unsigned int size() { return vecSize; }

  // Returns whether or not the vector has 0 elements
  bool empty() { return vecSize == 0; }

  // If pos is a valid position, retrieves the element in position pos in the
  // array, stores it in data, and returns true; otherwise, returns false
  bool at(unsigned int pos, T& data);

  // If the vector contains data, returns true; otherwise, returns false
  bool contains(const T& data);

  /******************************/
  /** Data insertion functions **/
  /******************************/

  // If the vector does not already contain data, adds
  // a new element, data, to the back of the vector
  bool insert(const T& data);

  // If the vector does not already contain data, adds
  // a new element, data, to position pos in the vector
  bool insert(const T& data, unsigned int pos);

  // If the vector does not already contain data, adds
  // a new element, data, to the front of the vector
  bool push_front(const T& data);

  /*****************************/
  /** Data removal functions **/
  /*****************************/

  // If the vector contains data, removes data from the vector
  bool remove(const T& data);

  // If pos is a valid position, removes the element in position pos, stores it in data
  bool remove(unsigned int pos, T& data);

  // If the vector is not empty, removes the last element in the vector, stores it in data
  bool pop_back(T& data);

  /**************************/
  /** Overloaded operators **/
  /**************************/

  // Equality is determined by two vectors having the same elements in the same order
  bool operator==(const UniqueVector& rhs);

  /*******************/
  /** Miscellaneous **/
  /*******************/

  // Empties the vector of its elements
  void clear();

private:
  T* arr;
  unsigned int vecSize;
  unsigned int vecCapacity;

  /******************************/
  /** Private helper functions **/
  /******************************/

  // Reallocates a newCapacity amount of space for the vector and copies the elements over
  void resize(unsigned int newCapacity);

  // Returns whether or not pos is a valid index given the current size of the vector
  bool isIndexOutOfBounds(unsigned int pos) { return (empty() || pos >= vecSize); }
};

// Note that in general, a header file should not include the associated implementation file;
// However, in the case of template classes, they need to be.
#include "UniqueVector.cpp"

#endif
