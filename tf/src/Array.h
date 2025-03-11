#ifndef ARRAY_H
#define ARRAY_H

#include "stddef.h"

extern const int INITIAL_ARRAY_SIZE;

/* Array.h - Header file defining a generic dynamic array structure used as a foundation for other structures.
 *
 * All methods expect the array to be passed by reference.
 *
 * Methods: 
 * createArray - Intializes a new array and returns it by value.
 * destoryArray - Deallocates the memory allocated for a referenced array.
 * appendArray - Appends the value at the given const void *, by the defined elementSize for a referenced array.
 * popArray - Removes the last element of the referenced array and returns a void* pointing to the element's value.
 *	 Note that this value could get overwritten at future Array method calls.
 * getElementArray - Returns a void* pointing to the value at the given index at the referenced array.
 */

typedef struct Array {
	void* elements;
	size_t arraySize;
	size_t elementCount;
	size_t elementSize;
} Array;

Array createArray(size_t elementSize);
void destroyArray(Array*);

void appendArray(Array*, const void*);
void* popArray(Array*);
void* getElementArray(const Array*, size_t index);


#endif // ARRAY_H
