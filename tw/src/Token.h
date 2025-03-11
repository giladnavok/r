#ifndef TOKEN_H_
#define TOKEN_H_

#include <stddef.h>
#include <stdbool.h>

#include "FilePosition.h"


typedef enum TokenType {
	TOKEN_INVALID = 0,
	TOKEN_NEWBLOCK,
	TOKEN_NEWCASE,
	TOKEN_ENDBLOCK,
	TOKEN_BEFORE_ALL,
	TOKEN_AFTER_ALL,
	TOKEN_BEFORE_EACH,
	TOKEN_AFTER_EACH,
	TOKEN_DATA,
	TOKEN_DATA_NO_WRAP,
	TOKEN_PREPROC,
	TOKEN_EXPECT_ALL,
	TOKEN_END_EXPECT_ALL,
	TOKEN_ASSERT_ALL,
	TOKEN_END_ASSERT_ALL,
	TOKEN_END_ALL,
	TOKEN_END_OF_FILE,
} TokenType;

bool isTokenTypeFullLine(const TokenType);

typedef struct KeywordTypeMapping {
	const char* keyword;
	TokenType type;
} KeywordTypeMapping;

extern const KeywordTypeMapping keywordTypeMappings[];
extern const int KEYWORD_TYPE_MAP_SIZE;


typedef struct Token {
	TokenType type;
	FilePosition filePosition;
} Token;

#endif // TOKEN_H
