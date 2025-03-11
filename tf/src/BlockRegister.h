#ifndef BLOCK_REGISTER_H
#define BLOCK_REGISTER_H

#include "Tree.h"

typedef struct BlockRegister {
	const char* blockName;
	TestBlock tb;
} BlockRegister;

BlockRegister createBlockRegister(const char*, TestBlock);

#endif // BLOCK_REGISTER_H
