#include <stdlib.h>
#include <stdbool.h>

const char* __CURRENT_NAME;
bool __PASS;
int __INDENT;
int __CURRENT_ID = 0;
int __TEST_START_LINE;

void* __NULLPTR = 0;


#define __PRE_TEST_BLOCK(name, id, indent) { \
	printf("%.*s%s: \n", indent - 1, "\t\t\t\t\t\t\t\t\t\t\t", name); \
} 

#define __PRE_TEST_CASE(name, id, indent) { \
	printf("%.*s(%d)%s: ", indent - 1, "\t\t\t\t\t\t\t\t\t\t\t", id, name); \
	__PASS = true; \
	__CURRENT_NAME = name; \
	__INDENT = indent; \
	__CURRENT_ID++; \
	__TEST_START_LINE = __LINE__ + 2; \
} 

#define __POST_TEST_CASE(name, indent) { \
	printf((__PASS)? "PASSED\n" : "FAILED\n"); \
} 

#define ASSERT(expr) { \
	if (!(expr)) { \
		printf("\n%.*s ", __INDENT - 1, "\t\t\t\t\t\t\t\t\t\t\t"); \
		printf("Assertion of " #expr " failed at:\n"); \
		printf("%.*s ", __INDENT - 1, "\t\t\t\t\t\t\t\t\t\t\t"); \
 		printf("%s:%d\n", __FILE__, __LINE__); \
		printf("%.*s ", __INDENT - 1, "\t\t\t\t\t\t\t\t\t\t\t"); \
 		printf("Test starts at line %d\n", __TEST_START_LINE); \
		__PASS = false; \
		printf("\n%.*s ", __INDENT - 1, "\t\t\t\t\t\t\t\t\t\t\t"); \
		__POST_TEST_CASE(__NAME, __INDENT); \
		exit(1); \
	} \
}

#define EXPECT(expr) { \
	if (!(expr)) { \
		printf("\n%.*s ", __INDENT - 1, "\t\t\t\t\t\t\t\t\t\t\t"); \
		printf("Expectation of " #expr " failed at:\n"); \
		printf("%.*s ", __INDENT - 1, "\t\t\t\t\t\t\t\t\t\t\t"); \
 		printf("%s:%d\n", __FILE__, __LINE__); \
		printf("%.*s ", __INDENT - 1, "\t\t\t\t\t\t\t\t\t\t\t"); \
 		printf("Test starts at line %d\n", __TEST_START_LINE); \
		__PASS = false; \
		printf("\n%.*s ", __INDENT - 1, "\t\t\t\t\t\t\t\t\t\t\t"); \
	} \
}

#define INCREMENT_TEST() \
	__POST_TEST_CASE(__CURRENT_NAME, __INDENT); \
	__PRE_TEST_CASE(__CURRENT_NAME, __CURRENT_ID, __INDENT);

#define ASSERT_THROW(expr, exception) \
	try { \
		expr; \
	} catch (const exception& e) { \
		ASSERT(1) \
	} catch (...) { \
		ASSERT(0)\
	} 
#define EXPECT_THROW(expr, exception) \
	try { \
		expr; \
	} catch (const exception& e) { \
		EXPECT(1) \
	} catch (...) { \
		EXPECT(0) \
	} 

	
