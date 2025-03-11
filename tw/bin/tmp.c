#include "include.h"
int main() {
	__PRE_TEST_BLOCK("a", 0, 1)
	{ 
		__PRE_TEST_BLOCK("ab", 0, 2)
		{ 
			__PRE_TEST_CASE("aa", 0, 3)
			{ 
			} 
			__POST_TEST_CASE("aa", 3)
		} 
		__PRE_TEST_BLOCK("ac", 1, 2)
		{ 
			__PRE_TEST_CASE("", 1, 3)
			{ 
			} 
			__POST_TEST_CASE("", 3)
		} 
	} 
	__PRE_TEST_BLOCK("new", 2, 1)
	{ 
		__PRE_TEST_BLOCK("a", 2, 2)
		{ 
			__PRE_TEST_CASE("", 2, 3)
			{ 
			} 
			__POST_TEST_CASE("", 3)
		} 
	} 
}
