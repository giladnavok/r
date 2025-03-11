#ifndef TEST_BLOCK_H
#define TEST_BLOCK_H

#include "Token.h"
#include "FilePosition.h"
#include "FilePositionArray.h"
#include "ChildrenArray.h"

#include <stdbool.h>
#include <stdio.h>

typedef struct TestBlockData {
	char* name;
	FilePositionArray beforeAll;
	FilePositionArray beforeEach;
	FilePositionArray afterEach;
	FilePositionArray afterAll;
} TestBlockData;

TestBlockData createTestBlockData();
void destroyTestBlockData(TestBlockData*);


typedef struct TestBlock {
	TestBlockData data;
	ChildrenArray childrenArray;
	FILE* src;
} *TestBlock;

typedef struct TestCase {
	char* name;
	FilePositionArray content;
	FILE* src;
} *TestCase;

TestBlock createTestBlock(FILE*);
TestCase createTestCase(FILE*);

TestBlock emplaceChildrenBlock(TestBlock, FILE*);
TestCase emplaceChildrenCase(TestBlock, FILE*);
ChildrenType getTestBlockType(const TestBlock tb);

TestBlock getTestBlockChildrenFromTestBlock(const TestBlock, int);
TestCase getTestCaseChildrenFromTestBlock(const TestBlock, int);
int getTestBlockSize(const TestBlock tb);

void destroyTestBlockRecursive(TestBlock);
void destroyTestCase(TestCase);

#endif // TEST_BLOCK_H
