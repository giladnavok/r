#include "FilePosition.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char *createStringFromFilePosition(FILE* src, FilePosition fp) {
	char* res = malloc(sizeof(*res) * fp.length + 1);
	if (res == NULL) {
		return NULL;
	}
	long int originalPosition = ftell(src);
	fseek(src, fp.pos, SEEK_SET);
	char *p = res;
	while(fp.length-- > 0) {
		*p++ = fgetc(src);
	}
	*p = 0;

	fseek(src, originalPosition, SEEK_SET);
	return res;
}

	
