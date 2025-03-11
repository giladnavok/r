#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct Lexer {
	FILE* file;
} Lexer;

Lexer createLexer();
void setLexerSourceFile(Lexer*, FILE*);

void destroyLexer(Lexer*);

Token lexerNextToken(Lexer*);
	
	


#endif // LEXER_H
