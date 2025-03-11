#include "FilePosition.h"
#include "Array.h"
#include "FilePositionArray.h"

#include <stdio.h>
#include <assert.h>

FilePositionArray createFilePositionArray() {
	FilePositionArray ret = {
		.filePositions = createArray(sizeof(FilePosition))};
	return ret;
}

void destroyFilePositionArray(FilePositionArray* fpa) {
	destroyArray(&fpa->filePositions);
}

void appendFilePositionArray(FilePositionArray* fpa, FilePosition filePosition) {
	appendArray(&fpa->filePositions, &filePosition);
}

int getFilePositionArraySize(const FilePositionArray* fpa) {
	return fpa->filePositions.elementCount;
}

FilePosition getFilePositionArray(const FilePositionArray* fpa, int index) {
	assert(index < fpa->filePositions.elementCount);
	return *((FilePosition*) getElementArray(&fpa->filePositions, index));
}

