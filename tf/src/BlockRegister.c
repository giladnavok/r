#include "BlockRegister.h"

BlockRegister createBlockRegister(const char* blockName, TestBlock tb) {
	BlockRegister ret = {
		.blockName = blockName, 
		.tb = tb};
	return ret;
}
