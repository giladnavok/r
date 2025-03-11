#ifndef RLE_LIST_HELPER_H
#define RLE_LIST_HELPER_H
#include "RLEList.h"

typedef struct Node_t {
	char value;
	int count;
	struct Node_t* next;
} *Node;


struct RLEList_t {
	int size;
	Node head;
	Node tail;
};

char dummyMap(char c);
char dummyMap1(char c);
char dummyMap2(char c);
char dummyMap3(char c);
bool testIfExportedStringMatches2(RLEList list, char* exportedString);
bool testIfMapped(RLEList listMapped, RLEList listNotMapped, MapFunction mapFunction);
bool testRLEListExportToString(RLEList list);
bool testListSize(RLEList list, int expectedSize);
bool compareStringsBySize(char* string1, char* string2, int size);
bool testListContent(RLEList list, char* expectedString);
bool testList(RLEList list, char* expectedContent, int expectedSize);
bool testRLEListGet(char* values);
void printRLEList(RLEList list);
bool testRLEListMap(char* values, MapFunction mapFunction);

#endif // RLE_LIST_HELPER_H
