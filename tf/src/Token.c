#include "Token.h"
#include <stdbool.h>

bool isTokenTypeFullLine(const TokenType type) {
	switch(type) {
		case TOKEN_DATA:
		case TOKEN_DATA_NO_WRAP:
		case TOKEN_PREPROC:
			return true;
		default:
			return false;
	}
}
const KeywordTypeMapping keywordTypeMappings[] = {
	{.keyword = "TEST_BLOCK", .type = TOKEN_NEWBLOCK},
	{.keyword = "TEST_CASE", .type = TOKEN_NEWCASE},
	{.keyword = "BEFORE_ALL", .type = TOKEN_BEFORE_ALL},
	{.keyword = "AFTER_ALL", .type = TOKEN_AFTER_ALL},
	{.keyword = "BEFORE_EACH", .type = TOKEN_BEFORE_EACH},
	{.keyword = "AFTER_EACH", .type = TOKEN_AFTER_EACH},
	{.keyword = "EXPECT_ALL", .type = TOKEN_EXPECT_ALL},
	{.keyword = "END_EXPECT_ALL", .type = TOKEN_END_EXPECT_ALL},
	{.keyword = "ASSERT_ALL", .type = TOKEN_ASSERT_ALL},
	{.keyword = "END_ASSERT_ALL", .type = TOKEN_END_ASSERT_ALL},
	{.keyword = "END_ALL", .type = TOKEN_END_ALL},
	{.keyword = "#", .type = TOKEN_PREPROC},
	{.keyword = "END_BLOCK", .type = TOKEN_ENDBLOCK},
};
const int KEYWORD_TYPE_MAP_SIZE = sizeof(keywordTypeMappings) / sizeof(KeywordTypeMapping);
