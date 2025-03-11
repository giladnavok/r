#include "Lexer.h"
#include "Token.h"
#include "common.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>

#define LEXER_PEEK_BUFFER_SIZE 25

// Calle needs to check for .file validity
Lexer createLexer() {
	Lexer l = {0};
	return l;
}

void setLexerSourceFile(Lexer* l, FILE* src) {
	l->file = src;
}
	

void destroyLexer(Lexer* l) {
	return;
}

char fpeekc(FILE* file) {
	char ch = getc(file);
	ungetc(ch, file);
	return ch;
}

void fpeekWordToBuffer(FILE* file, char buff[LEXER_PEEK_BUFFER_SIZE]) {
	fscanf(file, "%" STRING(LEXER_PEEK_BUFFER_SIZE) "s", buff);
	fseek(file, -strlen(buff), SEEK_CUR);
}

TokenType identifyKeyword(char buff[LEXER_PEEK_BUFFER_SIZE]) {
	for (int i = 0; i < KEYWORD_TYPE_MAP_SIZE; i++) {
		KeywordTypeMapping mapping = keywordTypeMappings[i];
		size_t keywordLength = strlen(mapping.keyword);
		if (strncmp(buff, mapping.keyword, keywordLength) == 0) {
			if (buff[keywordLength] == 0 
				|| (buff[keywordLength] == ':' 
					&& buff[keywordLength + 1] == 0)) {
				return mapping.type;
			} else {
				if (mapping.type == TOKEN_PREPROC) {
					return mapping.type;
				}
				break;
			}
		}
	}

	if (buff[0] == ':' || buff[0] == '/') {
		return TOKEN_DATA_NO_WRAP;
	}
	return TOKEN_DATA;
}

void trimLeftSpace(FILE* file) {
	char ch;
	while ((ch = fgetc(file)) && isspace(ch)) {}
	ungetc(ch, file);
}

void trimLeftSpaceNotIncludingNewline(FILE* file) {
	char ch;
	while ((ch = fgetc(file)) && isspace(ch) && ch != '\n') {}
	ungetc(ch, file);
}

char fgetcReverse(FILE* file) {
	char ch = fgetc(file);
	fseek(file, -2, SEEK_CUR);
	return ch;
}
	

void trimRightSpaceFromFilePosition(FILE* file, FilePosition *fp) {
	long int originalPosition = ftell(file);

	fseek(file, fp->pos + fp->length - 1, SEEK_SET);
	while (fp->length > 0 && isspace(fgetcReverse(file))) {
		fp->length--;
	}
	
	fseek(file, originalPosition, SEEK_SET);
	
}

Token lexerNextToken(Lexer *l) {
	Token t = {
			.type = TOKEN_INVALID,
			.filePosition = {0}};


	trimLeftSpace(l->file);

	if (feof(l->file)) {
		t.type = TOKEN_END_OF_FILE;
		return t;
	}

	if (fpeekc(l->file) == '\n') {
		UNREACHABLE("Should be unreachable because trimLeftSpace trims newlines as well");
		fgetc(l->file);
		return lexerNextToken(l);
	}
	
	// Detemining the type of the token
	char peekWordBuffer[LEXER_PEEK_BUFFER_SIZE];
	fpeekWordToBuffer(l->file, peekWordBuffer);
	t.type = identifyKeyword(peekWordBuffer);


	// Trims left space of some token types
	if (!isTokenTypeFullLine(t.type)) {
		fseek(l->file, strlen(peekWordBuffer), SEEK_CUR);
		trimLeftSpaceNotIncludingNewline(l->file);
	}

	// Fills the token's content
	t.filePosition.pos = ftell(l->file);

	if (t.type == TOKEN_DATA_NO_WRAP && peekWordBuffer[0] == ':') {
	t.filePosition.pos++;
	}
	
	char ch;
	while ((ch = fgetc(l->file)) != EOF &&
			ch != '\n') {
		t.filePosition.length++;
	}

	if (ch != EOF && isTokenTypeFullLine(t.type)) {
		//t.filePosition.length++;
	}

	// Trims right space of some token types
	if (!isTokenTypeFullLine(t.type)) {
		trimRightSpaceFromFilePosition(l->file, &t.filePosition);
	}
	
	return t;
}
	
	
	

