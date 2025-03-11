#include "Tree.h"
#include "FilePositionArray.h"

typedef struct Printer {
	FILE* dest;
	const char *currentName;
	int currentTestCaseId;
	int depth;

	
	bool expectall;


} Printer;


Printer createPrinter();
void destroyPrinter();
void printTree(Printer*, Tree* t);
