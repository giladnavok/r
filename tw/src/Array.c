#include "Array.h"
#include "string.h"
#include "assert.h"

#include <stdlib.h>

const int INITIAL_ARRAY_SIZE = 2;

Array createArray(size_t elementSize) {
	Array ret = {
		.elements = calloc(INITIAL_ARRAY_SIZE, elementSize),
		.arraySize = INITIAL_ARRAY_SIZE,
		.elementCount = 0,
		.elementSize = elementSize,
	};
	return ret;
}

void destroyArray(Array *ar) {
	assert(ar != NULL);
	free(ar->elements);
}

void* getElementArray(const Array *ar, size_t index) {
	assert(index < ar->arraySize);
	return (void*) (((char*) ar->elements) + index * ar->elementSize);
}
	

void expandArray(Array *ar) {
	ar->arraySize *= 2;
	ar->elements = realloc(ar->elements, ar->arraySize * ar->elementSize);
}

void expandArrayIfNeeded(Array *ar) {
	if (ar->elementCount == ar->arraySize) { 
		expandArray(ar);
	}
}

void appendArray(Array *ar, const void* element) {
	expandArrayIfNeeded(ar);
	memcpy(getElementArray(ar, ar->elementCount), element, ar->elementSize);
	ar->elementCount++;
}

void* popArray(Array *ar) {
	void* ret = getElementArray(ar, ar->elementCount - 1);
	ar->elementCount--;
	return ret;
}
