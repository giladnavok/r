#ifndef FILE_POSITION_ARRAY_H
#define FILE_POSITION_ARRAY_H

#include "FilePosition.h"
#include "Array.h"

#include <stdio.h>


typedef struct FilePositionArray {
	Array filePositions;
} FilePositionArray;

FilePositionArray createFilePositionArray();
void destroyFilePositionArray(FilePositionArray*);
void appendFilePositionArray(FilePositionArray*, FilePosition);

FilePosition getFilePositionArray(const FilePositionArray*, int);
int getFilePositionArraySize(const FilePositionArray* fpa);

#endif // FILE_POSITION_ARRAY_H
