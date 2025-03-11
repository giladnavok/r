#ifndef CHILDREN_ARRAY_H
#define CHILDREN_ARRAY_H
#include "Array.h"

typedef enum ChildrenType {
	CHILDREN_NOT_SET = 0, 
	CHILDREN_BLOCK, 
	CHILDREN_CASE
} ChildrenType;

typedef struct ChildrenArray {
	Array children;
	ChildrenType type;
} ChildrenArray;

ChildrenArray createChildrenArrayByType(ChildrenType);
void destroyChildrenArrayRecursive(ChildrenArray*);

void appendChildrenArray(ChildrenArray*, const void*);

int getChildrenArraySize(const ChildrenArray*);
void* getChildrenArray(const ChildrenArray* car, int index);
void* getLastChildrenArray(const ChildrenArray*);

int findNameInChildrenArray(const ChildrenArray*, const char*);

#endif // CHILDREN_ARRAY_H
