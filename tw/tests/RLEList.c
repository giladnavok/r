#include "RLEList.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

/* - - - - - - - - Helper functions - - - - - - - - */

static Node createNode(char value);
static int getIntLength(int n);
static int RLEListGetStringSize(RLEList list);
static void recompressListStartingAtNode(RLEList list, Node startingNode);
static void recompressWholeList(RLEList list);
static void RLEListRemoveNode(RLEList list, Node toRemove, Node previousNode);
static char internalRLEListGetRemove(RLEList list, int index, RLEListResult *result, bool remove);
static int printIntToString(char* string, int n);
static int printLine(char* string, char c, int n);

static Node createNode(char value) {
	Node newNode = malloc(sizeof(*newNode));
	if (newNode == NULL) {
		return NULL;
	}
	newNode->value = value;
	newNode->count = 1;
	newNode->next = NULL;
	return newNode;
}

static int getIntLength(int n) {
	int resultLength = 0;
	while (n > 0) {
		resultLength++;
		n /= 10;
	}
	return resultLength;
}

static int RLEListGetStringSize(RLEList list) {
	int resultSize = 0;
	Node current = list->head;
	while (current != NULL) {
		resultSize += 1 + getIntLength(current->count);
		resultSize++;
		current = current->next;
	}

	return resultSize + 1;
}

static void recompressListStartingAtNode(RLEList list, Node startingNode) {
	if (RLEListSize(list) <= 1) {
		return;
	}
	if (startingNode == NULL) {
		startingNode = list->head;
	}

	Node current = startingNode;
		
	while (current->next != NULL) {
		if (current->value == current->next->value) {
			current->count += current->next->count;
			RLEListRemoveNode(list, current->next, current);
		} else {
			current = current->next;
		}
	}
	return;
}

static void recompressWholeList(RLEList list) {
	recompressListStartingAtNode(list, list->head);
}

static void RLEListRemoveNode(RLEList list, Node toRemove, Node previousNode) {
	if (toRemove == list->head) {
		assert(previousNode == NULL);
		if (list->size == 1) {
			free(toRemove);
			list->head = NULL;
			list->tail = NULL;
		} else {
			list->head = toRemove->next;
			free(toRemove);
		}
		return;
	} else if (toRemove == list->tail) {
		list->tail = previousNode;
	}

	previousNode->next = toRemove->next;
	free(toRemove);
}

static char internalRLEListGetRemove(RLEList list, int index, RLEListResult *result, bool remove) {
	bool saveResult = (result != NULL);
	
	if (list == NULL) {
		if (saveResult) {
			*result = RLE_LIST_NULL_ARGUMENT;
		}
		return 0;
	}
	if (index < 0 || index >= list->size) {
		if (saveResult) {
			*result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
		}
		return 0;
	}


	Node previous = NULL;
	Node current = list->head;
	assert(current != NULL);
	int currentIndex = 0;
	while (current != NULL && (currentIndex + current->count) <= index) {
		currentIndex += current->count;
		previous = current;
		current = current->next;
	}

	char nodeValue = current->value;

	if (remove) {
		current->count--;
		if (current->count == 0) {
			RLEListRemoveNode(list, current, previous);
			recompressListStartingAtNode(list, previous);
		}
		list->size--;
			
	}
	if (saveResult) {
		*result = RLE_LIST_SUCCESS;
	}
	return nodeValue;
}

static int printIntToString(char* string, int n) {
	int intLength = getIntLength(n);
	int printingIndent = intLength - 1;
	while (printingIndent >= 0) {
		string[printingIndent] = (n % 10) + '0';
		n /= 10;
		printingIndent--;
	}

	return intLength;
}

static int printLine(char* string, char c, int n) {
	int printedChars = 0;

	string[printedChars++] = c;
	printedChars += printIntToString(string + printedChars, n);
	string[printedChars++] = '\n';

	return printedChars;
}

/* - - - - - - - - - - - - - - - - - - - - - - - */

//implement the functions here

RLEList RLEListCreate() {
	RLEList newList = malloc(sizeof(*newList));
	if (newList == NULL) {
		return NULL;
	}
	newList->head = NULL;
	newList->tail = NULL;
	newList->size = 0;
	return newList;
}

void RLEListDestroy(RLEList list) {
	if (list == NULL) {
		return;
	}
	Node currentNode = list->head;
	while (currentNode != list->tail) {
		Node nextNode = currentNode->next;
		free(currentNode);
		currentNode = nextNode;
	}
	free(list->tail);
	free(list);
	return;
}


RLEListResult RLEListAppend(RLEList list, char value) {
	if (list == NULL) {
		return RLE_LIST_NULL_ARGUMENT;
	}

	if (list->size == 0) {
		Node newNode = createNode(value);
		if (newNode == NULL) {
			return RLE_LIST_OUT_OF_MEMORY;
		}
		list->head = newNode;
		list->tail = newNode;

	} else if (list->tail->value == value) {
		list->tail->count++;

	} else {
		Node newNode = createNode(value);
		if (newNode == NULL) {
			return RLE_LIST_OUT_OF_MEMORY;
		}
		list->tail->next = newNode;
		list->tail = newNode;
	}

	list->size++;
	return RLE_LIST_SUCCESS;
}


char* RLEListExportToString(RLEList list, RLEListResult* result) {
	bool saveResult = (result != NULL);
	if (list == NULL) {
		if (saveResult) { 
			*result = RLE_LIST_NULL_ARGUMENT;
		}
		return NULL;
	}
	int stringSize = RLEListGetStringSize(list);
	char* resultString = malloc(sizeof(*resultString) * stringSize);
	if (resultString == NULL) {
		if (saveResult) { 
			*result = RLE_LIST_OUT_OF_MEMORY;
		}
		return NULL;
	}
	Node current = list->head;
	char* currentStringPosition = resultString;
	while (current != NULL) {
		currentStringPosition += printLine(
			currentStringPosition,
			current->value,
			current->count
		);
		current = current->next;
	}
	*currentStringPosition = '\0';
	if (saveResult) { 
		*result = RLE_LIST_SUCCESS;
	}
	return resultString;
}

int RLEListSize(RLEList list) {
	if (list == NULL) {
		return -1;
	}
	return list->size;
}


char RLEListGet(RLEList list, int index, RLEListResult *result) {
	return internalRLEListGetRemove(list, index, result, false);
}
RLEListResult RLEListRemove(RLEList list, int index) {
	RLEListResult result;
	internalRLEListGetRemove(list, index, &result, true);
	return result;
}

RLEListResult RLEListMap(RLEList list, MapFunction mapFunction) {
	if (list == NULL || mapFunction == NULL) {
		return RLE_LIST_NULL_ARGUMENT;
	}
	Node current = list->head;
	while (current != NULL) {
		current->value = mapFunction(current->value);
		current = current->next;
	}
	recompressWholeList(list);
	
	return RLE_LIST_SUCCESS;
}
	


	

