#ifndef FILE_POSITION_OPTIONS_H
#define FILE_POSITION_OPTIONS_H

#include "Options.h"
#include <stdbool.h>

#define HEADER_FILE_POSITION_OPTION(name, option) \
void setFilePositionOption##name(FilePositionOptions*); \
void unsetFilePositionOption##name(FilePositionOptions*); \
bool isSetFilePositionOption##name(FilePositionOptions*); 

enum FILE_POSITION_OPTION {
	FILE_POSITION_OPTION_WRAP_ASSERT = 1 << 0,
	FILE_POSITION_OPTION_WRAP_EXPECT = 1 << 1
};

typedef struct Options FilePositionOptions;

FilePositionOptions createFilePositionOptions();

HEADER_FILE_POSITION_OPTION(WrapAssert, FILE_POSITION_OPTION_WRAP_ASSERT)
HEADER_FILE_POSITION_OPTION(WrapExpect, FILE_POSITION_OPTION_WRAP_EXPECT)



#endif //  FILE_POSITION_OPTIONS_H
