#ifndef FILE_ARRAY_H
#define FILE_ARRAY_H
#include <stdio.h>

typedef Array FileArray;

FileArray createFileArray();
void destroyFileArray(FileArray*);

void appendFileArray(FileArray*, FILE*);

FILE* getFileArray(FileArray*, int index);
	

#endif // FILE_ARRAY_H
