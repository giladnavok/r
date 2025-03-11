#include "Options.h"
#include "FilePositionOptions.h"
#include <stdbool.h>

#define IMPLEMENT_FILE_POSITION_OPTION(name, option) \
void setFilePositionOption##name(FilePositionOptions* fpopt) { \
	setOption(fpopt, option); \
} \
void unsetFilePositionOption##name(FilePositionOptions* fpopt) { \
	unsetOption(fpopt, option); \
} \
bool isSetFilePositionOption##name(FilePositionOptions* fpopt) { \
	return isOptionSet(fpopt, option); \
} 

FilePositionOptions createFilePositionOptions() {
	return createOptions();
}

IMPLEMENT_FILE_POSITION_OPTION(WrapExpect, FILE_POSITION_OPTION_WRAP_EXPECT)
IMPLEMENT_FILE_POSITION_OPTION(WrapAssert, FILE_POSITION_OPTION_WRAP_ASSERT)
