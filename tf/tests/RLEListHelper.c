#include "RLEListHelper.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


/* - - - - - - Helper functions - - - - - - -  - - - - - - */

#define GET_FIRST_NODE(l) l->head
#define LAST_MALLOC_SIZE 10

 char dummyMap(char c) {
	return c + 1;
}

 char dummyMap1(char c) {
	return (c%2) * '\n';
}

 char dummyMap2(char c) {
	return '\n';
}

 char dummyMap3(char c) {
	return 0;
}

 bool testIfExportedStringMatches2(RLEList list, char* exportedString) {
	Node current = GET_FIRST_NODE(list);
	char value;
	int count;
	int size = RLEListSize(list);
	while (size > 0) {
		value = *exportedString++;
		sscanf(exportedString, "%d", &count);
		if (current == NULL || current->value != value || current->count != count) {
			printf("\nExported string does not match the list's content\n");
			return false;
		}
		current = current->next;
		if (count <= 0) {
			printf("\nList contains an invalid node with count <= 0\n");
			return false;
		}
		size -= count;
		while (*exportedString != '\n') {
			if (*exportedString == '\0') {
				printf("\nExported string formatting is wrong, maybe missing \\n at the end\n");
			}
			exportedString++;
		}
		exportedString++;
	}
	if (size != 0) {
		printf("\nInvalid count of list's last node\n");
		return false;
	}
	return true;
}
 bool testIfMapped(RLEList listMapped, RLEList listNotMapped, MapFunction mapFunction) {
	Node currentMapped = GET_FIRST_NODE(listMapped);
	Node currentNotMapped = GET_FIRST_NODE(listNotMapped);
	while (currentMapped != NULL && currentNotMapped != NULL) {
		if (currentMapped->value != mapFunction(currentNotMapped->value)) {
			return false;
		}
		currentMapped = currentMapped->next;
		currentNotMapped = currentNotMapped->next;
	}
	return true;
}
 bool testRLEListExportToString(RLEList list) {
	RLEListResult result;
	bool pass = true;
	char *exportedString = RLEListExportToString(list, &result);	
	switch(result) {
		case RLE_LIST_SUCCESS:
			pass = testIfExportedStringMatches2(list, exportedString);
			break;
		default:
			printf("\nRLEListExportToString didn't return RLE_LIST_SUCCESS but %d\n", result);
	}
	free(exportedString);
	return pass;
}

 bool testListSize(RLEList list, int expectedSize) {
	int size = 0;
	Node current = GET_FIRST_NODE(list);
	while (current != NULL) {
		size += current->count;
		current = current->next;
	}
	bool pass = true;
	if (size != RLEListSize(list)) {
		printf("\nRLEListSize does not match list's actual size\n");
		pass = false;
	}
	if (size != expectedSize) {
		printf("\nList size does not match expected size\n");
		pass = false;
	}
	return pass;
}
	
 bool compareStringsBySize(char* string1, char* string2, int size) {
	while (size-- > 0) {
		if (string1[size] != string2[size]) {
			return false;
		}
	}
	return true;
}

 bool testListContent(RLEList list, char* expectedString) {
	bool pass = true;
	if (!testRLEListExportToString(list)) {
		printf("\nRLEListExportToString does not match list's actual content\n");
		pass = false;
	}
	char* exportedString = RLEListExportToString(list, NULL);
	if (!compareStringsBySize(exportedString, expectedString, LAST_MALLOC_SIZE)) {
		printf("\nExported string does not match expected string:");
		printf("\n*Expected string:\n%s[END]", expectedString);
		printf("\n*Exported string:\n%s[END]\n", exportedString);
		pass = false;
	} 
	free(exportedString);
	return pass;
}

 bool testList(RLEList list, char* expectedContent, int expectedSize) {
	return  testListContent(list, expectedContent) &&
			testListSize(list, expectedSize);
}	

 bool testRLEListGet(char* values) {
	RLEList list = RLEListCreate();
	if (list == NULL) {
		printf("\nFailed to create RLE list\n");
		return false;
	}
	bool pass = true;
	RLEListResult result;

	for (int i = 0; i < strlen(values); i++) {
		result = RLEListAppend(list, values[i]);
	}
	
	for(int i = 0; i < RLEListSize(list); i++) {
		if (RLEListGet(list, i, &result) != values[i]) {
			printf("\nRLEListGet failed to get index %d of RLE list of %s\n",
					i, values);
			pass = false;
		} else if (result != RLE_LIST_SUCCESS) {
			printf("\nRLEListGet didn't set result to RLE_LIST_SUCCESS on success\n");
			pass = false;
		}
	}

	RLEListDestroy(list);
	return pass;
}
 void printRLEList(RLEList list) {
	char* exportedString = RLEListExportToString(list, NULL);
	printf("%s[END]\n", exportedString);
	free(exportedString);
}
		
 bool testRLEListMap(char* values, MapFunction mapFunction) {
	bool pass = true;
	RLEList listNotMapped = RLEListCreate();
	if (listNotMapped == NULL) {
		printf("\nFailed to create RLE list\n");
		return false;
	}
	RLEList listMapped = RLEListCreate();
	if (listMapped== NULL) {
		RLEListDestroy(listNotMapped);
		printf("\nFailed to create RLE list\n");
		return false;
	}

	for (int i = 0; i < strlen(values); i++) {
		RLEListAppend(listNotMapped, values[i]);
		RLEListAppend(listMapped,values[i]);
	}

	if (RLEListMap(listMapped, mapFunction) != RLE_LIST_SUCCESS) {
		printf("\nRLEListMap did not return RLE_LIST_SUCCESS\n");
		pass = false;
	}
	if (!testIfMapped(listMapped, listNotMapped, mapFunction)) {
		printf("\nRLEListMap did not map currectly:\n");
		printf("Original list:\n");
		printRLEList(listNotMapped);
		printf("Mapped list:\n");
		printRLEList(listMapped);
		pass = false;
	}
	

	RLEListDestroy(listNotMapped);
	RLEListDestroy(listMapped);
	return pass;
}
/* - - - - - - End of helper functions - - - - - - - - - - - - - - */
	
