/**
 * @file dynamicarray.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.4
 * @date September 24, 2024
 *
 * Implements a DynamicArray template class defined in the 'dynamicarray.h' header file.
 */
 
#include <iostream>
#include <string>
#include "dynamicarray.h"

using namespace std;


/**
 * Implements all functions of the DynamicArray template class. Default capacity is 10.
 * @tparam Type T data contained in the array.
*/

/** @brief Default Constructor
 *
*/

template <typename T>
DynamicArray<T>::DynamicArray(): _capacity(DEFAULT_CAP), _size(0), _elements(new T[DEFAULT_CAP]) {}

/** @brief Regular Constructor
 *
*/

template <typename T>
DynamicArray<T>::DynamicArray(int capacity): _capacity(capacity), _size(0), _elements(new T[capacity]) {}

/** @brief Copy constructor. Deep copies from another dynamic array.
 *
 *  Deep copies another dynamic array's capacity, size, and elements.
 *
 *  @param other The source dynamic array containing the capacity, size, 
 *  and elements. 
 *  
*/

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other): _capacity(other._capacity), _size(other._size), _elements(new T[_capacity]) {
    for (int i = 0; i < _size; i++) {
        _elements[i] = other._elements[i];
    }
}

/** @brief Move constructor. Shallow copies from another dynamic array.
 *
 *  Shallow copies an R-value dynamic array's capacity, size, and elements pointer.
 *  Ensures the R-value's elements pointer is empty after assignment
 *
 *  @param other The source dynamic array containing the capacity, size, 
 *  and elements.
 *  
*/

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& temp): _capacity(temp._capacity), _size(temp._size), _elements(temp._elements) {
    temp._elements = nullptr;
}

/** @brief Destructor. Clears every element from the dynamic array.
 * 
*/

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] _elements;
}

/** @brief Returns the dynamic array's capacity.
 *
 *  @return The capacity of the dynamic array. 
*/

template <typename T>
int DynamicArray<T>::capacity() const {
    return _capacity;
}

/** @brief Inserts a new element into the dynamic array.
 *
 *  Inserts a new element into the dynamic array at the rightmost index. If the
 *  size exceeds the capacity, expand is called and a new array with 
 *  double the capacity is created. Increases the size by one.
 *
 *  @param element The element value to be inserted into the dynamic array.
 *  @return Void.
*/

template <typename T>
void DynamicArray<T>::insert(T& element) {
    if (this->isFull()) {
        this->expand();
    }
    _elements[_size] = element;
    _size++;
}

/** @brief Returns the dynamic array's current size.
 * 
 *  @return The current size of the dynamic array.
*/  

template <typename T>
int DynamicArray<T>::size() const {
    return _size;
}

/** @brief Checks if the dynamic array is empty or not.
 *
 *  A dynamic array is empty if its current size is 0.
 *
 *  @return True if it is empty, and false if it is not empty.
*/

template <typename T>
bool DynamicArray<T>::isEmpty() const {
    return _size == 0;
}

/** @brief Checks if the dynamic array is full or not. 
 *
 *  A dynamic array is full if its current size equals its capacity.
 *
 *  @return Returns true if it is full, and false if it is not full.
*/

template <typename T>
bool DynamicArray<T>::isFull() const {
    return _size == _capacity;
}

/** @brief Searches for a specific element in the dynamic array.
 *
 *  Iteratively searches for the passed element value within the array.
 *  Returns an invalid index if the element is not found in the array.
 *
 *  @param element The element value being searched for.
 *  @return The index of the element being searched for. 
 *          Returns -1 if the element is not found.
*/

template <typename T>
int DynamicArray<T>::search(T element) const {
    for (int i = 0; i < _size; i++) {
        if (element == _elements[i]) {
            return i;
        }
    }
    return -1;
}

/** @brief Removes an element at a specific index from the dynamic array.
 *
 *  Removes the element at the passed index. Shifts everything to the right of that element
 *  one index to the left, ensuring there are no gaps in the array. Decreases the size
 *  by one.
 *
 *  @param index The index of the element being removed from the dynamic array.
 *  @return Void.
*/

template <typename T>
void DynamicArray<T>::remove(int index) {
    if (index < 0 || index >= _size) {
        throw("Index is out of bounds!");
    } 
    for (int i = index; i < _size - 1; i++) {
        _elements[i] = _elements[i+1];
    }
    _size--;

}

/** @brief Decreases the size of the dynamic array by 1.
 *
 *  @return Void.
*/

template <typename T>
void DynamicArray<T>::decSize() {
    _size--;
}

/** @brief Clears the dynamic array by setting the size to 0.
 *
 *  @return Void.
*/

template <typename T>
void DynamicArray<T>::clear() {
    _size = 0;
} 

/** @brief Creates a new dynamic array with double the capacity of the old one.
 *
 *  Copies all elements from the existing array into the new array.
 *  Frees the memory from the full array and makes the existing array pointer 
 *  point to the new array.
 *
 *  @return Void.
*/

template <typename T>
void DynamicArray<T>::expand() {
        T* tempArray = new T[_capacity * 2];
        for (int i = 0; i < _size; i++) {
            tempArray[i] = _elements[i];
        }
        _elements = tempArray;
        _capacity = _capacity * 2; 
}

/** @brief Copy assignmnt. Deep copies the values from another dynamic array.
 *
 *  Overloads the assignment (=) operator so that it does the following:
 *  Copies element values in the same order from a source dynamic array to the current
 *  dynamic array. The two arrays should be equal after the copy.
 *
 *  @param other The source dynamic array containing the capacity, size,   
 *  elements pointer, and elements.
 *  @return The updated version of the dynamic array.
 */

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator = (const DynamicArray& other) {
    if (this == &other) {
        return *this;
    }

    _size = other._size;
    _capacity = other._capacity;
    _elements = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _elements[i] = other._elements[i];
    }
    return *this;
}

/** @brief Move assignmnt. Shallow copies from another dynamic array.
 *
 *  Overloads the assignment (=) operator so that it does the following:
 *  Copies an R-value dynamic array's capacity, size, and elements, assigning it a new name.
 *  Ensures the temporary R-value dynamic array's pointers are null after assignment.
 *
 *  @param temp An R-value dynamic array containing the capacity, size,   
 *  elements pointer, and elements.
 *  @return The updated version of the dynamic array.
 */

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator = (DynamicArray&& temp) {
    if (this == &temp) {
        return *this;
    }
    _size = temp._size;
    _capacity = temp._capacity;
    _elements = temp._elements;
    temp._elements = nullptr;
    return *this;
}

/** @brief Returns the element in the dynamic array at the passed index value.
 *
 *  Overloads the index ([]) operator so that it does the following:
 *  Returns the appropriate element in the array based on the passed index parameter.
 *  If the passed index is out-of-bounds (e.g. a negative index or an index greater than size),
 *  then an error is given to the user. This function is able to be used on constant dynamic arrays.
 *
 *  @param index The index of the element the user wishes to access.
 *  @return The element in the dynamic array at the passed index.
 */

template <typename T>
T DynamicArray<T>::operator [] (const int index) const {
    if (index < 0 || index > _size) {
        throw invalid_argument("Index is out of bounds!");
    } else {
        return _elements[index];
    }
}

/** @brief Returns the address of the element in the dynamic array at the passed index value.
 *
 *  Overloads the index ([]) operator so that it does the following:
 *  Returns the appropriate address of the element in the array based on the passed index parameter.
 *  If the passed index is out-of-bounds (e.g. a negative index or an index greater than size),
 *  then an error is given to the user. 
 *
 *  @param index The index of the element the user wishes to access.
 *  @return The memory address of the element in the dynamic array at the passed index.
 */

template <typename T>
T& DynamicArray<T>::operator [] (const int index) {
    if (index < 0 || index > _size) {
        throw invalid_argument("Index is out of bounds!");
    } else {
        return _elements[index];
    }
}

template class DynamicArray<Job>;