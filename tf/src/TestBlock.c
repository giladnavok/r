#include "Tree.h"
#include "assert.h"
#include "FilePositionArray.h"
#include "ChildrenArray.h"
#include <stdlib.h>

TestBlockData createTestBlockData() {
	TestBlockData ret = {
		.name = NULL,
		.beforeAll = createFilePositionArray(),
		.beforeEach = createFilePositionArray(),
		.afterEach = createFilePositionArray(),
		.afterAll = createFilePositionArray()
	};
	return ret;
}

void destroyTestBlockData(TestBlockData* tbd) {
	free(tbd->name);
	destroyFilePositionArray(&tbd->beforeAll);
	destroyFilePositionArray(&tbd->beforeEach);
	destroyFilePositionArray(&tbd->afterEach);
	destroyFilePositionArray(&tbd->afterAll);
}

TestBlock createTestBlock(FILE* src) {
	TestBlock ret = calloc(1, sizeof(*ret));
	ret->data = createTestBlockData();
	ret->childrenArray.type = CHILDREN_NOT_SET;
	ret->src = src;
	
	return ret;
}

TestCase createTestCase(FILE* src) {
	TestCase ret = calloc(1, sizeof(*ret));
	ret->name = NULL;
	ret->content = createFilePositionArray();
	ret->src = src;
	return ret;
}

TestBlock emplaceChildrenBlock(TestBlock tb, FILE* src) {
	assert(tb->childrenArray.type != CHILDREN_CASE);
	if (tb->childrenArray.type == CHILDREN_NOT_SET) {
		 tb->childrenArray = createChildrenArrayByType(CHILDREN_BLOCK);
	}
	appendChildrenArray(&tb->childrenArray, createTestBlock(src));
	return *((TestBlock*) getLastChildrenArray(&tb->childrenArray));
}

TestCase emplaceChildrenCase(TestBlock tb, FILE* src) {
	assert(tb->childrenArray.type != CHILDREN_BLOCK);
	if (tb->childrenArray.type == CHILDREN_NOT_SET) {
		tb->childrenArray = createChildrenArrayByType(CHILDREN_CASE);
	}
	appendChildrenArray(&tb->childrenArray, createTestCase(src));
	return *((TestCase*) getLastChildrenArray(&tb->childrenArray));
}
	
void destroyTestCase(TestCase tc) {
	destroyFilePositionArray(&tc->content);
	free(tc->name);
	free(tc);
}

void destroyTestBlockRecursive(TestBlock tb) {
	destroyChildrenArrayRecursive(&tb->childrenArray);
	destroyTestBlockData(&tb->data);
	free(tb);
}

ChildrenType getTestBlockType(const TestBlock tb) {
	return tb->childrenArray.type;
}

TestBlock getTestBlockChildrenFromTestBlock(const TestBlock tb, int index) {
	assert(getTestBlockType(tb) == CHILDREN_BLOCK);
	return *((TestBlock*) getChildrenArray(&tb->childrenArray, index));
}
TestCase getTestCaseChildrenFromTestBlock(const TestBlock tb, int index) {
	assert(getTestBlockType(tb) == CHILDREN_CASE);
	return *((TestCase*) getChildrenArray(&tb->childrenArray, index));
}

int getTestBlockSize(const TestBlock tb) {
	return getChildrenArraySize(&tb->childrenArray);
}
