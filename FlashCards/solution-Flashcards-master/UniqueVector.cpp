#ifndef __CS235_UNIQUE_VECTOR_CPP_
#define __CS235_UNIQUE_VECTOR_CPP_

#include "UniqueVector.h"

template<class T>
bool UniqueVector<T>::at(unsigned int pos, T& data) {
  if (isIndexOutOfBounds(pos)) {
    return false;
  }

  data = arr[pos];

  return true;
}

template<class T>
bool UniqueVector<T>::contains(const T& data) {
  for (unsigned int i = 0; i < vecSize; i++) {
    if (arr[i] == data) {
      return true;
    }
  }
  return false;
}

template<class T>
bool UniqueVector<T>::insert(const T& data) {
  // Even if insertion at the back is quite simple, this is still efficient because
  // insert(data, pos) ultimately does not do any more iteration than it has to
  return insert(data, size());
}

template<class T>
bool UniqueVector<T>::insert(const T& data, unsigned int pos) {
  if (contains(data) || pos > size()) {
    return false;
  }

  if (vecSize == vecCapacity) {
    resize(vecCapacity * 2);
  }

  // Shifts all of the elements to the right to
  // accomodate extra element
  for (unsigned int i = vecSize; i > pos; i--) {
    arr[i] = arr[i-1];
  }
  arr[pos] = data;
  vecSize++;

  return true;
}

template<class T>
bool UniqueVector<T>::push_front(const T& data) {
  return insert(data, 0);
}

template<class T>
bool UniqueVector<T>::remove(unsigned int pos, T& data) {
  if (isIndexOutOfBounds(pos)) {
    return false;
  }

  data = arr[pos];
  for (unsigned int i = pos; i < vecSize-1; i++) {
    arr[i] = arr[i+1];
  }
  vecSize--;

  return true;
}

template<class T>
bool UniqueVector<T>::remove(const T& data) {
  // Instead of calling contains and therefore requiring two passes
  // through the vector (once for contains and once more to remove),
  // this function looks for data and then removes it upon finding it
  for (unsigned int i = 0; i < vecSize; i++) {
    if (arr[i] == data) {
      // Shifts elements to the left to fill the gap of the element to be removed
      for (unsigned int j = i; j < vecSize-1; j++) {
	arr[j] = arr[j+1];
      }
      vecSize--;
      return true;
    }
  }
  return false;
}

template<class T>
bool UniqueVector<T>::pop_back(T& data) {
  if (empty()) {
    return false;
  }

  data = arr[vecSize-1];
  vecSize--;

  return true;
}

template<class T>
void UniqueVector<T>::clear() {
  // This could technically be implemented as only a few variable changes,
  // but this is visually clearer and allows for future changes in the code.
  // Resizing might require more steps in the future, so this allows us
  // to leverage and future-proof clear's functionality now. Ultimately,
  // calling resize here does not do any more iterations than necessary.
  vecSize = 0;
  resize(3);
}

template<class T>
bool UniqueVector<T>::operator==(const UniqueVector<T>& rhs) {
  // Note how we can access rhs' private instance variables
  if (vecSize != rhs.vecSize || vecCapacity != rhs.vecCapacity) {
    return false;
  }

  for (unsigned int i = 0; i < vecSize; i++) {
    if (arr[i] != rhs.arr[i]) {
      return false;
    }
  }

  return true;
}

// Private helper functions

template<class T>
void UniqueVector<T>::resize(unsigned int newCapacity) {
  vecCapacity = newCapacity;
  T* oldArr = arr;
  arr = new T[vecCapacity];
  // Copies the elements over
  for (unsigned int i = 0; i < vecSize; i++) {
    arr[i] = oldArr[i];
  }
  delete[] oldArr;
}

#endif
