#include "Printer.h"
#include "FilePosition.h"
#include "Array.h"
#include "FilePositionOptions.h"

#include <stdarg.h>


const char* INDENT = "\t\t\t\t\t\t\t\t\t\t\t\t";

Printer createPrinter(FILE* dest, FILE* src) {
	Printer ret = {
		.dest = dest,
		.currentName = "",
		.depth = 0,
		.currentTestCaseId = 0
	};
	return ret;
}

void destroyPrinter(Printer* p) {
	return;
}

void fprintfIndent(FILE* dest, int indentWidth) {
	fprintf(dest, "%.*s", indentWidth, INDENT);
}

void printTestBlockRecursive(Printer *p, TestBlock tb);

void fprintfWithIndent(FILE* dest, int indentWidth, const char * format, ...) {
	va_list args;
	va_start(args, format);
	fprintfIndent(dest, indentWidth);
	vfprintf(dest, format, args);
	va_end(args);
}


void printPreFilePosition(FILE* dest, FilePosition fp) {
	if (isSetFilePositionOptionWrapExpect(&fp.opt)) {
		fprintf(dest, "EXPECT(");
	} else if (isSetFilePositionOptionWrapAssert(&fp.opt)) {
		fprintf(dest, "ASSERT(");
	}
}

bool printPostFilePosition(FILE* dest, FilePosition fp) {
	if (isSetFilePositionOptionWrapExpect(&fp.opt) ||
		isSetFilePositionOptionWrapAssert(&fp.opt)) {
		fprintf(dest, ");\n");
		return true;
	}
	return false;
}


void fprintFilePositionWithIndent(FILE* dest, FILE* src, FilePosition fp, int indentWidth) {
	long int originalPosition = ftell(src);
	fseek(src, fp.pos, SEEK_SET);

	fprintfIndent(dest, indentWidth);
	printPreFilePosition(dest, fp);
	for (int i = 0; i < fp.length - 1; i++) {
		fprintf(dest, "%c", fgetc(src));
	}
	char lastChar = fgetc(src);

	if (!printPostFilePosition(dest, fp)) {
		fprintf(dest, "%c\n", lastChar);
	}
	fflush(dest);

	fseek(src, originalPosition, SEEK_SET);
}

void fprintFilePositionArrayWithIndent(FILE* dest, FILE* src, FilePositionArray* fpa, int indentWidth) {
	for (size_t i = 0; i < getFilePositionArraySize(fpa); i++) {
		FilePosition fp = getFilePositionArray(fpa, i);
		fprintFilePositionWithIndent(dest, src, fp, indentWidth);
	}
}

void fprintFilePositionArrayWithSourcesWithIndent(FILE* dest, FileArray* sources, FilePositionArray* fpa, int indentWidth) {
	for (size_t i = 0; i < getFilePositionArraySize(fpa); i++) {
		FilePosition fp = getFilePositionArray(fpa, i);
		FILE* src = getFileArray(sources, i);
		fprintFilePositionWithIndent(dest, src, fp, indentWidth);
	}
}

void fprintTestCase(FILE* dest, FILE* src, TestCase tc, int depth) {
	fprintfWithIndent(dest, depth, "{ // ");
	fprintfWithIndent(dest, 0, "%s", tc->name);
	fprintFilePositionArrayWithIndent(dest, tc->src, &tc->content, depth + 1);
	fprintfWithIndent(dest, depth, "} // ");
	fprintfWithIndent(dest, 0, "%s", tc->name);
}

void printFilePosition(Printer* p, FILE* src, FilePosition fp) {
	fprintFilePositionWithIndent(p->dest, src, fp, p->depth);
}

void printString(Printer* p, const char* str) {
	fprintfWithIndent(p->dest, p->depth, str);
}

void printFilePositionArray(Printer* p, FILE* src, FilePositionArray* fpa) {
	fprintFilePositionArrayWithIndent(p->dest, src, fpa, p->depth);
}

void printFilePositionArrayWithSources(Printer* p, FileArray* sources, FilePositionArray* fpa) {
	fprintFilePositionArrayWithSourcesWithIndent(p->dest, sources, fpa, p->depth);
}

const char *preTestCase = "__PRE_TEST_CASE(\"%s\", %d, %d)\n";

void printPreTestCase(Printer *p) {
	fprintfWithIndent(p->dest, p->depth, preTestCase, p->currentName, p->currentTestCaseId, p->depth);
	fprintfWithIndent(p->dest, p->depth, "{ \n", p->currentName);
	// Optional settings here
}

const char *preTestBlock = "__PRE_TEST_BLOCK(\"%s\", %d, %d)\n";

void printPreTestBlock(Printer *p) {
	fprintfWithIndent(p->dest, p->depth, preTestBlock, p->currentName, p->currentTestCaseId, p->depth);
	fprintfWithIndent(p->dest, p->depth, "{ \n", p->currentName);
	// Optional settings here
}

void printPostTestBlock(Printer *p) {
	fprintfWithIndent(p->dest, p->depth, "} \n", p->currentName);
	// Optional settings here
}
const char *postTestCase = "__POST_TEST_CASE(\"%s\", %d)\n";

void printPostTestCase(Printer *p) {
	fprintfWithIndent(p->dest, p->depth, "} \n", p->currentName);
	fprintfWithIndent(p->dest, p->depth, postTestCase, p->currentName, p->depth);
	// Optional settings here
}

const char *preRoot = "#include \"include.h\"\n";

void printPreproc(Printer* p, Tree* t) {
	int tmp;
	fprintf(p->dest, preRoot, &tmp);
	printFilePositionArrayWithSources(p, &t->preprocSources, &t->preproc);
	fprintf(p->dest, "int main() {\n");
}

void printChildrenBlocksRecursive(Printer *p, TestBlock tb) {
	for (int i = 0; i < getTestBlockSize(tb); i++) {
		TestBlock childTestBlock = getTestBlockChildrenFromTestBlock(tb, i);
		p->currentName = childTestBlock->data.name;

		//Pre TestBlock
		printFilePositionArray(p, tb->src, &tb->data.beforeEach);
		printPreTestBlock(p);

		p->depth++;
		printTestBlockRecursive(p, childTestBlock);
		p->depth--;
		// Post testBlock

		printPostTestBlock(p);
		printFilePositionArray(p, tb->src, &tb->data.afterEach);
	}
}

void printChildrenCases(Printer *p, TestBlock tb) {
	for (int i = 0; i < getTestBlockSize(tb); i++) {
		TestCase childTestCase = getTestCaseChildrenFromTestBlock(tb, i);
		p->currentName = childTestCase->name;
		printFilePositionArray(p, tb->src, &tb->data.beforeEach);
		printPreTestCase(p);
		p->depth++;
		printFilePositionArray(p, childTestCase->src, &childTestCase->content);
		p->depth--;
		printPostTestCase(p);
		printFilePositionArray(p, tb->src, &tb->data.afterEach);
		p->currentTestCaseId++;
	}
}
	
	
void printTestBlockRecursive(Printer *p, TestBlock tb) {

	printFilePositionArray(p, tb->src, &tb->data.beforeAll);

	if (tb->childrenArray.type == CHILDREN_BLOCK) {
		printChildrenBlocksRecursive(p, tb);
	} else if (tb->childrenArray.type == CHILDREN_CASE) {
		printChildrenCases(p, tb);
	}

	printFilePositionArray(p, tb->src, &tb->data.afterAll);
}

void printTree(Printer* p, Tree* t) {
	printPreproc(p, t);
	p->depth = 1;
	printTestBlockRecursive(p, t->root);
	fprintf(p->dest, "}\n");
}
