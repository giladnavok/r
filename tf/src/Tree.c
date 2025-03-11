#include "Tree.h"
#include "TestBlock.h"
#include "FilePositionArray.h"
#include "FileArray.h"

Tree createTree(FILE* src) {
	Tree ret = {
		.root = createTestBlock(src),
		.preproc = createFilePositionArray(),
		.preprocSources = createFileArray()
	};
	return ret;
}

void destroyTree(Tree* t) {
	destroyTestBlockRecursive(t->root);
	destroyFilePositionArray(&t->preproc);
	destroyFileArray(&t->preprocSources);
}
	

