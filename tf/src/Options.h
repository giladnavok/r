#ifndef OPTION_H
#define OPTION_H

#include <stdbool.h>
/* General options module to be wrapped and used in other modules */

typedef struct Options {
	int opt;
} Options;

Options createOptions();
void setOption(Options* op, int option);
void unsetOption(Options* op, int option);
bool isOptionSet(Options* op, int option);
	


#endif //  OPTION_H
