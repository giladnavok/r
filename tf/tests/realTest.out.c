#include "include.h"
#include "RLEList.h"
#include "RLEListHelper.h"
#include "RLEList.h" // Sourced from second file
#include "RLEList.h" // Sourced from third file
int main() {
	__PRE_TEST_BLOCK("RLEList.h", 0, 1)
	{ 
		__PRE_TEST_BLOCK("NULL", 0, 2)
		{ 
			RLEList l = RLEListCreate();
			RLEListResult result;
			ASSERT((void*)l != __NULLPTR);
			__PRE_TEST_CASE("RLEListExportToString", 0, 3)
			{ 
				EXPECT(0);
				EXPECT(RLEListExportToString(NULL,NULL) == __NULLPTR);
			} 
			__POST_TEST_CASE("RLEListExportToString", 3)
			__PRE_TEST_CASE("RLEListAppend", 1, 3)
			{ 
				EXPECT(RLEListAppend(NULL, 0) == RLE_LIST_NULL_ARGUMENT);
			} 
			__POST_TEST_CASE("RLEListAppend", 3)
			__PRE_TEST_CASE("RLEListGet", 2, 3)
			{ 
				EXPECT(RLEListGet(NULL, 0, &result) == 0);
				EXPECT(result == RLE_LIST_NULL_ARGUMENT);
			} 
			__POST_TEST_CASE("RLEListGet", 3)
			__PRE_TEST_CASE("", 3, 3)
			{ 
				EXPECT(RLEListMap(NULL, dummyMap) == RLE_LIST_NULL_ARGUMENT);
			} 
			__POST_TEST_CASE("", 3)
			__PRE_TEST_CASE("RLEListMap", 4, 3)
			{ 
				EXPECT(RLEListMap(l, NULL) == RLE_LIST_NULL_ARGUMENT);
			} 
			__POST_TEST_CASE("RLEListMap", 3)
			__PRE_TEST_CASE("RLEListDestory", 5, 3)
			{ 
				EXPECT(RLEListRemove(NULL, 0) == RLE_LIST_NULL_ARGUMENT);
			} 
			__POST_TEST_CASE("RLEListDestory", 3)
			__PRE_TEST_CASE("", 6, 3)
			{ 
				EXPECT(RLEListRemove(l, 0) == RLE_LIST_INDEX_OUT_OF_BOUNDS);
			} 
			__POST_TEST_CASE("", 3)
			RLEListDestroy(l);
		} 
		__PRE_TEST_BLOCK("General", 7, 2)
		{ 
			RLEList l;
			RLEListResult result;
			l = RLEListCreate();
			ASSERT((void*)l != __NULLPTR);
			__PRE_TEST_BLOCK("RLEListGet", 7, 3)
			{ 
				__PRE_TEST_CASE("Lower bound", 7, 4)
				{ 
					EXPECT(RLEListGet(l, -1, &result) == 0);
				} 
				__POST_TEST_CASE("Lower bound", 4)
				__PRE_TEST_CASE("Lower bound result", 8, 4)
				{ 
					EXPECT(result == RLE_LIST_INDEX_OUT_OF_BOUNDS);
				} 
				__POST_TEST_CASE("Lower bound result", 4)
				__PRE_TEST_CASE("Upper bound", 9, 4)
				{ 
					EXPECT(RLEListGet(l, RLEListSize(l), &result) != 0);
				} 
				__POST_TEST_CASE("Upper bound", 4)
				__PRE_TEST_CASE("Upper bound result", 10, 4)
				{ 
					EXPECT(result != RLE_LIST_INDEX_OUT_OF_BOUNDS);
				} 
				__POST_TEST_CASE("Upper bound result", 4)
				__PRE_TEST_CASE("Full get tests", 11, 4)
				{ 
					EXPECT(testRLEListGet(""));
					EXPECT(testRLEListGet("abc"));
					EXPECT(testRLEListGet("abbbbbbbcccc"));
					EXPECT(testRLEListGet("aaaaaaaaaaaaaaaac"));
				} 
				__POST_TEST_CASE("Full get tests", 4)
			} 
			RLEListDestroy(l);
			l = RLEListCreate();
			ASSERT((void*)l != __NULLPTR);
			__PRE_TEST_BLOCK("RLEListAppend", 12, 3)
			{ 
				__PRE_TEST_CASE("Append", 12, 4)
				{ 
					RLEListAppend(l, 'a');
					RLEListAppend(l, 'b');
					for (int i = 0; i < 5; i++) {
					RLEListAppend(l, 'a');
					}
					ASSERT(testList(l, "a1\nb1\na5\n", 7));
				} 
				__POST_TEST_CASE("Append", 4)
				__PRE_TEST_CASE("Append many", 13, 4)
				{ 
					for (int i = 0; i < 1000; i++) { 
					RLEListAppend(l, 'a');
					}
					for (int i = 0; i < 1000; i++) { 
					RLEListAppend(l, 'b');
					}
					for (int i = 0; i < 10000; i++) { 
					RLEListAppend(l, 'a');
					}
					EXPECT(testList(l,"a1\nb1\na1005\nb1000\na10000\n", 12007));
				} 
				__POST_TEST_CASE("Append many", 4)
			} 
			RLEListDestroy(l);
			l = RLEListCreate();
			ASSERT((void*)l != __NULLPTR);
			__PRE_TEST_BLOCK("RLEListGet from third file", 14, 3)
			{ 
				__PRE_TEST_CASE("Lower bound", 14, 4)
				{ 
					EXPECT(RLEListGet(l, -1, &result) == 0);
				} 
				__POST_TEST_CASE("Lower bound", 4)
				__PRE_TEST_CASE("Lower bound result", 15, 4)
				{ 
					EXPECT(result == RLE_LIST_INDEX_OUT_OF_BOUNDS);
				} 
				__POST_TEST_CASE("Lower bound result", 4)
				__PRE_TEST_CASE("Upper bound", 16, 4)
				{ 
					EXPECT(RLEListGet(l, RLEListSize(l), &result) != 0) ;
				} 
				__POST_TEST_CASE("Upper bound", 4)
				__PRE_TEST_CASE("Upper bound result", 17, 4)
				{ 
					EXPECT(result != RLE_LIST_INDEX_OUT_OF_BOUNDS);
				} 
				__POST_TEST_CASE("Upper bound result", 4)
				__PRE_TEST_CASE("Full get tests", 18, 4)
				{ 
					// STARTS HERE
					EXPECT(testRLEListGet(""));
					EXPECT(testRLEListGet("abc"));
					EXPECT(testRLEListGet("abbbbbbbcccc"));
					EXPECT(testRLEListGet("aaaaaaaaaaaaaaaac"));
					// ENDS  HERE
				} 
				__POST_TEST_CASE("Full get tests", 4)
			} 
			RLEListDestroy(l);
		} 
	} 
	__PRE_TEST_BLOCK("RLEList.h from second file", 19, 1)
	{ 
		__PRE_TEST_BLOCK("General", 19, 2)
		{ 
			RLEList l;
			RLEListResult result;
			l = RLEListCreate();
			ASSERT((void*)l != __NULLPTR);
			__PRE_TEST_BLOCK("RLEListGet from third file", 19, 3)
			{ 
				__PRE_TEST_CASE("Lower bound", 19, 4)
				{ 
					EXPECT(RLEListGet(l, -1, &result) == 0);
				} 
				__POST_TEST_CASE("Lower bound", 4)
				__PRE_TEST_CASE("Lower bound result", 20, 4)
				{ 
					EXPECT(result == RLE_LIST_INDEX_OUT_OF_BOUNDS);
				} 
				__POST_TEST_CASE("Lower bound result", 4)
				__PRE_TEST_CASE("Upper bound", 21, 4)
				{ 
					EXPECT(RLEListGet(l, RLEListSize(l), &result) != 0) ;
				} 
				__POST_TEST_CASE("Upper bound", 4)
				__PRE_TEST_CASE("Upper bound result", 22, 4)
				{ 
					EXPECT(result != RLE_LIST_INDEX_OUT_OF_BOUNDS);
				} 
				__POST_TEST_CASE("Upper bound result", 4)
				__PRE_TEST_CASE("Full get tests", 23, 4)
				{ 
					EXPECT(testRLEListGet(""));
					EXPECT(testRLEListGet("abc"));
					EXPECT(testRLEListGet("abbbbbbbcccc"));
					EXPECT(testRLEListGet("aaaaaaaaaaaaaaaac"));
				} 
				__POST_TEST_CASE("Full get tests", 4)
			} 
			RLEListDestroy(l);
		} 
	} 
	__PRE_TEST_BLOCK("RLEList.h from third file", 24, 1)
	{ 
		__PRE_TEST_BLOCK("General", 24, 2)
		{ 
			RLEList l;
			RLEListResult result;
			l = RLEListCreate();
			ASSERT((void*)l != __NULLPTR);
			__PRE_TEST_BLOCK("RLEListGet from third file", 24, 3)
			{ 
				__PRE_TEST_CASE("Lower bound", 24, 4)
				{ 
					EXPECT(RLEListGet(l, -1, &result) == 0);
				} 
				__POST_TEST_CASE("Lower bound", 4)
				__PRE_TEST_CASE("Lower bound result", 25, 4)
				{ 
					EXPECT(result == RLE_LIST_INDEX_OUT_OF_BOUNDS);
				} 
				__POST_TEST_CASE("Lower bound result", 4)
				__PRE_TEST_CASE("Upper bound", 26, 4)
				{ 
					EXPECT(RLEListGet(l, RLEListSize(l), &result) != 0) ;
				} 
				__POST_TEST_CASE("Upper bound", 4)
				__PRE_TEST_CASE("Upper bound result", 27, 4)
				{ 
					EXPECT(result != RLE_LIST_INDEX_OUT_OF_BOUNDS);
				} 
				__POST_TEST_CASE("Upper bound result", 4)
				__PRE_TEST_CASE("Full get tests", 28, 4)
				{ 
					EXPECT(testRLEListGet(""));
					EXPECT(testRLEListGet("abc"));
					EXPECT(testRLEListGet("abbbbbbbcccc"));
					EXPECT(testRLEListGet("aaaaaaaaaaaaaaaac"));
				} 
				__POST_TEST_CASE("Full get tests", 4)
			} 
			RLEListDestroy(l);
		} 
	} 
}
