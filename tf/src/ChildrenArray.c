#include "ChildrenArray.h"
#include "Tree.h"
#include "Array.h"

#include <assert.h>
#include <string.h>

ChildrenArray createChildrenArrayByType(ChildrenType type) {
	ChildrenArray ret = {0};
	if (type == CHILDREN_BLOCK) {
		ret.children = createArray(sizeof(TestBlock*));
		ret.type = CHILDREN_BLOCK;
	} else {
		ret.children = createArray(sizeof(TestCase*));
		ret.type = CHILDREN_CASE;
	}
	return ret;
}

void destroyChildrenArrayRecursive(ChildrenArray* car) {
	assert(car);
	if (car->type == CHILDREN_BLOCK) {
		for (int i = 0; i < car->children.elementCount; i++) {
			TestBlock tb = ((TestBlock*) car->children.elements)[i];
			destroyTestBlockRecursive(tb);
		}
	} else if (car->type == CHILDREN_CASE) {
		for (int i = 0; i < car->children.elementCount; i++) {
			TestCase tc = ((TestCase*) car->children.elements)[i];
			destroyTestCase(tc);
		}
	}

	destroyArray(&car->children);
}
	
// Assumes user appends right type
void appendChildrenArray(ChildrenArray* car, const void* element) {
	assert(car);
	appendArray(&car->children, &element);
}

void* getChildrenArray(const ChildrenArray* car, int index) {
	assert(car);
	assert(index < car->children.elementCount);
	return getElementArray(&car->children, index);
}

void* getLastChildrenArray(const ChildrenArray* car) {
	assert(car);
	return getElementArray(&car->children, car->children.elementCount - 1);
}

int getChildrenArraySize(const ChildrenArray* car) {
	assert(car);
	return car->children.elementCount;
}

int findNameInChildrenArray(const ChildrenArray* car, const char* name) {
	assert(car);
	if (car->type == CHILDREN_BLOCK) {
		for (int i = 0; i < car->children.elementCount; i++) {
			TestBlock tb = ((TestBlock*) car->children.elements)[i];
			if (strcmp(tb->data.name, name) == 0) {
				return i;
			}
		}
	} else if (car->type == CHILDREN_CASE) {
		for (int i = 0; i < car->children.elementCount; i++) {
			TestCase tc = ((TestCase*) car->children.elements)[i];
			if (strcmp(tc->name, name) == 0) {
				return i;
			}
		}
	}

	return -1;
}

	
