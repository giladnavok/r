#ifndef TREE_H
#define TREE_H

#include "TestBlock.h"
#include "FilePositionArray.h"
#include "FileArray.h"

typedef struct Tree {
	TestBlock root;
	FilePositionArray preproc;
	FileArray preprocSources;
} Tree;

Tree createTree(FILE*);
void destroyTree(Tree*);


#endif // TREE_H


