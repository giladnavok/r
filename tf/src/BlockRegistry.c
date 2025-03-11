#include "BlockRegistry.h"
#include "Array.h"
#include "BlockRegister.h"
#include "Tree.h"

#include <string.h>

BlockRegistry createBlockRegistry() {
	return createArray(sizeof(BlockRegister));
}

void destroyBlockRegistry(BlockRegistry* br) {
	destroyArray(br);
}

void appendBlockRegistry(BlockRegistry* br, const char* blockName, TestBlock tb) {
	BlockRegister reg = createBlockRegister(blockName, tb);
	appendArray(br, &reg);
}


TestBlock loopupBlockRegistry(BlockRegistry* br,  const char* blockName) {
	BlockRegister* reg = br->elements;
	for (int i = 0; i< br->elementCount; i++) {
		if (strcmp(reg->blockName, blockName) == 0) {
			return reg->tb;
		}
		reg++;
	}
	return NULL;
}
	


