#ifndef FILE_POSITION_H
#define FILE_POSITION_H


#include <stdio.h>
#include <stdbool.h>

#include "FilePositionOptions.h"

typedef struct FilePosition {
	long int pos;
	size_t length;
	FilePositionOptions opt;
} FilePosition;

char* createStringFromFilePosition(FILE*, FilePosition);

#endif // FILE_POSITION_H
