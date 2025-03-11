#ifndef PARSER_H
#define PARSER_H

#include "Tree.h"
#include "FilePositionArray.h"
#include "Token.h"
#include "TestBlockTrace.h"
#include "FilePositionOptions.h"


typedef struct Parser {
	Tree* tree;
	TestBlock current;
	TestCase currentCase;
	TestBlockTrace trace;
	FilePositionArray* dataTarget;
	
	FilePositionOptions filePositionOptions;
} Parser;

Parser createParser(Tree* root);
void destroyParser(Parser*);

void parse(Parser*, FILE* src, Token*);





#endif // PARSER_H
