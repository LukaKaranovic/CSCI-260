/**
 * @file dynamicarray.h
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.4
 * @date September 24, 2024
 *
 * Defines a DynamicArray template class.
 * This class can be used with any data type.
 * A DynamicArray object starts with a fixed capacity but can be expanded when the array grows
 * beyone the capacity.
 */

#ifndef ASSN1_DYNAMICARRAY_H
#define ASSN1_DYNAMICARRAY_H

#include "job.h"

const int DEFAULT_CAP = 10;

template <typename T>
class DynamicArray {

	private:
		int _capacity; 	// The capacity of the array
		int _size;		// Counts the number of elements in the array
		T* _elements;	// Actual array that contains the elements.
    
	public:
		/**
		 * Default constructor
		 */
		DynamicArray();
		
		/**
		 * Regular constructor
		 */
		DynamicArray(int capacity);

		/**
		 * Copy constructor
		 */
		DynamicArray(const DynamicArray<T>& other);

		/**
		 * Move constructor
		 */
		DynamicArray(DynamicArray&& temp);

		/**
		 * Destructor
		 */
		~DynamicArray();

		/**
		 * Returns maximum number of elements that this dynamic array can hold.
		 */
		int capacity() const;
		
		/**
		 * Inserts an element into the array.
		 */
		void insert(T& element);

		/**
		 * Returns the current number of elements in the dynamic array.
		 */
		int size() const;

		/**
		 * Returns true if the dynamic array does not contain any element.
		 */
		bool isEmpty() const;
		
        /**
		 * Returns true if the dynamic array is full.
		 */
		bool isFull() const;

		/**
		 * Searches for the element in the dynamic array.
		 */
		int search(const T element) const;

		/**
		 * Removes the element at the index from the dynamic array.
		 */
		void remove(const int index);

		/**
		 * Decreases the size of the dynamic array by 1.
		 */
		void decSize();

		/**
		 * Removes all the elements from the dynamic array.
		 */
		void clear();

        /**
		 * Doubles the capacity of the dynamic array.
		 */
        void expand();

		/**
		 * Copy assignment
		 */
		DynamicArray<T>& operator = (const DynamicArray<T>& other);

		/**
		 * Move assignment
		 */
		DynamicArray& operator = (DynamicArray&& temp);

		/**
		 * Returns the element at the specified index from the collection
		 */
		T operator [] (const int index) const;
		
		/**
		 * Returns the address of the element at the specified index 
		 * from the collection
		 */
		T& operator [] (const int index);	
	
};

#endif