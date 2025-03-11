#ifndef BLOCK_REGISTRY_H
#define BLOCK_REGISTRY_H

#include "Array.h"
#include "Tree.h"

typedef Array BlockRegistry;

BlockRegistry createBlockRegistry();
void destroyBlockRegistry(BlockRegistry*);

void appendBlockRegistry(BlockRegistry*, const char*, TestBlock);

// Returns NULL in case not found;
TestBlock lookupBlockRegistry(BlockRegistry*, const char*);


#endif // BLOCK_REGISTRY_H


