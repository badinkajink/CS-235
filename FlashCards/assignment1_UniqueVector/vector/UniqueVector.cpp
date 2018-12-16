#ifndef CS235_UNIQUE_VECTOR_CPP
#define CS235_UNIQUE_VECTOR_CPP

#include <iostream>
#include <string>
#include <stdexcept>
#include "UniqueVector.h"

using namespace std; 	// make std members visible


// constructor: allocate an array of  3 elements.
template <typename T>
UniqueVector<T>::UniqueVector ()
{
	elem = new T[3];
	iCapacity = 3;
	iSize = 0;
}

// constructor: allocate an array of num elements.
template <typename T>
UniqueVector<T>::UniqueVector (int num)
{
	if (num < 0)
		throw length_error{"UniqueVector constructor: negative size"};

	elem = new T[num];

	iCapacity = num;
	iSize = 0;
}

// destructor: deallocate the storage.
template <typename T>
UniqueVector<T>::~UniqueVector ()
{
	delete[] elem;
}

//The subscript operator is needed by equality operator when comparing two vectors.
template <typename T>
T& UniqueVector<T>::operator[](unsigned int i)
{
	if (i < 0 || size() <=i)
		throw out_of_range{"UniqueVector::operator[]"};
	return elem[i];
}

//return the size of the space currently allocated for the vector.
template <typename T>
unsigned int UniqueVector<T>::capacity()
{
	return iCapacity;
}

//return the current number of elements in the vector.
template <typename T>
unsigned int UniqueVector<T>::size()
{
	return iSize;
}

//check if vector has zero elements.
template <typename T>
bool UniqueVector<T>::empty()
{
	if (iSize == 0)
		return true;
	else
		return false;
}

//if the vector contains data.
template <typename T>
bool UniqueVector<T>::contains(const T& data)
{
	if (isDataFoundInVector(data))
		return true;
	else
		return false;
}

//retrieve the element at position pos if it exists.
template <typename T>
bool UniqueVector<T>::at(unsigned int pos, T& data)
{
	if (pos < 0 || pos >= iSize)
		return false;

	data = elem[pos];
	//cout << "pos=" << pos << " in the vector; element value=" << data << "\n";
	cout << "pos=" << pos << " in the vector; element value=\n";
	return true;
}

//helper function to check if data already exists, thus not unique.
template <typename T>
bool UniqueVector<T>::isDataFoundInVector(const T& data)
{
	for (unsigned int i=0; i<iSize; i++)
	{
		if (elem[i]==data) {
			//cout << "Found " << data << " in the vector element i=" << i << ". Return without adding it.\n";
			cout << "Found in the vector element i=" << i << ". Return without adding it.\n";
			return true;
		}
	}
	return false;
}

//helper function to double the capacity of the array, and copy the existing array to the new one.
template <typename T>
void UniqueVector<T>::doubleCapacity()
{
	T* newElem;

	cout << " number of elements is: " << iSize << "; and the capacity is: " << iCapacity << "; Need to double capacity first.\n";
	newElem = new T[iCapacity*2];

	for (unsigned int i=0; i<iSize; i++)
		newElem[i] = elem[i];

	delete[] elem;  // deallocate the memory in the existing vector.

	elem = newElem;
	iCapacity *= 2;
}

//insert the data if it doesn't exist yet.
template <typename T>
bool UniqueVector<T>::insert(const T& data)
{
	if (isDataFoundInVector(data))
		return false;

	if (iSize == iCapacity) 
		doubleCapacity();

	//cout << data << " is not Found in the existing vector element. adding it to the vector.\n";
	cout << " is not Found in the existing vector element. adding it to the vector.\n";
	elem[iSize]=data;
	iSize++;

	return true;
}

//insert the data at position pos if it doesn't exist yet.
template <typename T>
bool UniqueVector<T>::insert(const T& data, unsigned int pos)
{
	// pos is out of bound if it is less than 0
	// pos can't be greater than iSize as if would create a gap between the last element in Vector and this position.
	if (pos < 0 || pos > iSize)
		return false;

        if (isDataFoundInVector(data))
                return false;

        if (iSize == iCapacity) 
                doubleCapacity();

        //cout << data << " is not Found in the existing vector element. adding it to the vector.\n";
        cout << " is not Found in the existing vector element. adding it to the vector.\n";
	if ( (iSize == 0) || (pos == iSize)) {
		// insert into the empty list or at the end of the non-empty list.
        	elem[iSize]=data;
	} else {
		// shift the list one spot to the left and ends at the pos.
		for (unsigned int end=iSize; end > pos; end--) {
			elem[end]=elem[end-1];
		}
		// insert the data to the requested position.
		elem[pos]=data;
	}
	iSize++;

        return true;
}

//insert the data to the beginng if it doesn't exist yet.
template <typename T>
bool UniqueVector<T>::push_front(const T& data)
{
	if (isDataFoundInVector(data))
		return false;

	if (iSize == iCapacity) 
		doubleCapacity();

	//cout << data << " is not Found in the existing vector element. adding it to the vector.\n";
	cout << " is not Found in the existing vector element. adding it to the vector.\n";
	if (iSize > 0) {
		// shift the whole list one spot to the left.
		for (unsigned int end=iSize; end > 0; end--) {
			elem[end]=elem[end-1];
		}
	}
	// either insert into the empty list or the first position of the non-empty list.
	elem[0]=data;
	iSize++;

	return true;
}

//helper function to find the exact pos of data to be removed.
template <typename T>
bool UniqueVector<T>::foundDataToRemove (unsigned int& pos, const T& data) 
{
	bool bFound=false;

	// if not a empty list, we will search through the list for data.
	for (unsigned int i=0; i<iSize; i++)
	{
		if (elem[i]==data) {
			bFound = true;
			pos = i;
			//cout << "Found " << data << " in the vector element i=" << i << ". It wil be removed.\n";
			cout << "Found in the vector element i=" << i << ". It wil be removed.\n";
			break;
		}
	}

	return bFound;
}

//helper function to remove data at pos and shift the remaining elements one spot to the left.
template <typename T>
void UniqueVector<T>::removeDataAtPos (unsigned int pos, T& data) 
{
	data = elem[pos];

	// if data is not the only element in the list, or not the last element in the list
	if ( !((iSize == 1) || (pos == iSize -1)) ) {
		// shift the list one spot to the right and begins at the pos.
		for (unsigned int begin=pos; begin < iSize-1; begin++) {
			cout << "removeDataAtPos for " << begin;
			elem[begin] = elem[begin+1];	
		} 
	}
	iSize--;
}

//remove data from vector if it exists.
template <typename T>
bool UniqueVector<T>::remove(const T& data)
{
	bool bFound=false;
	unsigned int pos=0;
	T tempData;

	bFound = foundDataToRemove (pos, data);

	if (bFound) {
		removeDataAtPos(pos, tempData);
	}

	return bFound;
}

//remove data from position pos if it exists.
template <typename T>
bool UniqueVector<T>::remove(unsigned int pos, T& data)
{
	// the list is empty
	// pos is out of bound if it is less than 0
	// pos can't be greater than iSize as if would create a gap between the last element in Vector and this position.
	if (iSize == 0 || pos < 0 || pos > iSize)
		return false;

	removeDataAtPos (pos, data);

	return true;
}

//remmve the last element from the vector.
template <typename T>
bool UniqueVector<T>::pop_back(T& data)
{
	// if the list is empty.
	if (iSize == 0)
		return false;

	//store the value of last element of the list.
	data = elem[iSize-1];
	iSize--;

	return true;
}

//deallocates the existing storage, and then reallocates an array of 3 elements.
template <typename T>
void UniqueVector<T>::clear()
{
	delete[] elem;  // deallocate the memory in the existing vector.

	elem = new T[3];
	iCapacity = 3;
	iSize = 0;
}

//equality operator to compare two vectors.
template <typename T>
bool UniqueVector<T>::operator==(UniqueVector<T>& rightV)
{
	unsigned int iSize1=0, iSize2=0;

	iSize1=iSize;
	iSize2=rightV.size();	

	// Two vectors have different size.
	if (iSize1 != iSize2)
		return false;

	// Both vectors are empty.  
	if (iSize1 == 0)
		return true;

	for (unsigned int i=0; i < iSize; i++) {
		if (elem[i] != rightV[i]) {
			//cout << "leftVector at pos=" << i << " is " << elem[i] << "; but the rightVector is " << rightV[i] << ".\n";
			cout << "leftVector at pos=" << i << " is ; but the rightVector is .\n";
			return false;
		}
	}

	return true;
}

/*
int main ()
{
//	UniqueVector<double> v(s);
	UniqueVector<double> v;

	double dValue = 0;

	if (v.empty())
		cout << "the vector is empty.\n";

	v.insert(1);
	if (!v.empty())
		cout << "the vector is not empty.\n";

	v.insert(2);
	v.insert(1);
	v.insert(30);
	v.insert(4);
	v.insert(5);
	v.insert(6);
	if (v.contains(3))
		cout << "the vector contains value 3.\n";

	if (!v.contains(7))
		cout << "the vector doesn't contain value 7.\n";

	if (v.at(2,dValue))
		cout << "pos=2 in the vector; element value from read_and_sum=" << dValue << ".\n";

	if (!v.at(-2,dValue))
		cout << "the pos -2 is false.\n";

	v.insert(10,-2);
	v.insert(10,0);
	v.insert(40,4);
	v.insert(10,20);
	v.insert(90,8);
	v.push_front(100);
	v.remove(90);
	v.remove(100);
	v.remove(300);
	v.remove(30);
	v.remove(3,dValue);
		cout << "pos=3 in the vector; element value remove=" << dValue << ".\n";

	v.pop_back(dValue);
		cout << "element value pop back=" << dValue << ".\n";


        UniqueVector<double> testVector1;
        UniqueVector<double> testVector2;
        if ( testVector1 == testVector2 ) 
		cout << "both vectors are empty, thus equal.\n";
	else
		cout << "both vectors are empty, but not equal???\n";

        testVector1.insert(0);
        if ( testVector1 == testVector2 ) 
		cout << "vector1 has one element, but vector2 is empty, but why are they equal???\n";
	else
		cout << "vector1 has one element, but vector2 is empty, they are not equal.\n";

        testVector1.insert(1);
        testVector1.insert(2);
        testVector1.insert(3);

        testVector2.insert(0);
        testVector2.insert(1);
        testVector2.insert(2);
        testVector2.insert(3);
        if ( testVector1 == testVector2 ) 
		cout << "both vectors have 4 identical values, so they shall be equal.\n";
	else
		cout << "both vectors have 4 identical values, but they are not equal???\n";


        testVector1.pop_back(dValue);
        testVector1.insert(40);
        if ( testVector1 == testVector2 ) 
		cout << "The value of the last element in two vectors are different. but why are they equal???\n";
	else
		cout << "The value of the last element in two vectors are different. thus, are not equal.\n";


	double sum=0;
	int tempVal=0;
	for (unsigned int i=0; i!=v.size(); ++i) {
		tempVal=v[i];
		sum += tempVal;
		cout << "the value at pos=" << i << " is " << tempVal << ".\n";
	}

	cout << "the sum is: " << sum << "\n";
}
*/

#endif
