#include "Array.h"
#include "FileArray.h"
#include <stdio.h>

FileArray createFileArray() {
	return createArray(sizeof(FILE*));
}
void destroyFileArray(FileArray* fa) {
	destroyArray(fa);
}

void appendFileArray(FileArray* fa, FILE* file) {
	appendArray(fa, &file);
}

FILE* getFileArray(FileArray* fa, int index) {
	return *((FILE**) getElementArray(fa, index));
}
