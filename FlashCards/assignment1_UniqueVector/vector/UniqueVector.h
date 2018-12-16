#ifndef CS235_UNIQUE_VECTOR_H
#define CS235_UNIQUE_VECTOR_H

template<typename T>

class UniqueVector {
private:
	T* elem;		//elem points to an array of type T.
	unsigned int iCapacity; //The size of the space allocated for the vector.
	unsigned int iSize;	//The actual number of elements in the vector.

public:
	UniqueVector();		// constructor: allocate an array of  3 elements.
	UniqueVector(int num);	// constructor: allocate an array of num elements.
	~UniqueVector(); 	// destructor: deallocate the storage.

	T& operator[](unsigned int i); 	//The subscript operator is needed by equality operator when comparing two vectors.

	unsigned int capacity();	//return the size of the space currently allocated for the vector.
	unsigned int size();		//return the current number of elements in the vector. 
	bool empty();			//check if vector has zero elements.
	bool contains(const T& data);			//if the vector contains data.
	bool at(unsigned int pos, T& data);		//retrieve the element at position pos if it exists.

	bool isDataFoundInVector(const T& data);	//helper function to check if data already exists, thus not unique.
	void doubleCapacity();				//helper function to double the capacity of the array, and copy the existing array to the new one.

	bool insert(const T& data);			//insert the data if it doesn't exist yet.
	bool insert(const T& data, unsigned int pos);	//insert the data at position pos if it doesn't exist yet.
	bool push_front(const T& data);			//insert the data to the beginng if it doesn't exist yet.

	bool foundDataToRemove (unsigned int& pos, const T& data);	//helper function to find the exact pos of data to be removed.
	void removeDataAtPos (unsigned int pos, T& data);		//helper function to remove data at pos and shift the remaining elements one spot to the left.

	bool remove(const T& data);			//remove data from vector if it exists.
	bool remove(unsigned int pos, T& data);		//remove data from position pos if it exists.
	bool pop_back(T& data);				//remmve the last element from the vector.
	void clear(); 					//deallocates the existing storage, and then reallocates an array of 3 elements.

	bool operator==(UniqueVector<T>& rightV);	//equality operator to compare two vectors.
};

#include "UniqueVector.cpp"
#endif
