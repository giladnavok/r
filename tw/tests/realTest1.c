#include "RLEList.h"
#include "RLEListHelper.h"

TEST_BLOCK: RLEList.h     
	TEST_BLOCK: NULL       
		BEFORE_ALL:
			RLEList l = RLEListCreate();
			RLEListResult result;
			ASSERT((void*)l != __NULLPTR);
		AFTER_ALL:
			RLEListDestroy(l);

		TEST_CASE: RLEListExportToString
			EXPECT(0);
			EXPECT(RLEListExportToString(NULL,NULL) == __NULLPTR);

		TEST_CASE: RLEListAppend
			EXPECT(RLEListAppend(NULL, 0) == RLE_LIST_NULL_ARGUMENT);

		TEST_CASE: RLEListGet
			EXPECT(RLEListGet(NULL, 0, &result) == 0);
			EXPECT(result == RLE_LIST_NULL_ARGUMENT);

		TEST_CASE:		
			EXPECT(RLEListMap(NULL, dummyMap) == RLE_LIST_NULL_ARGUMENT);

		TEST_CASE: RLEListMap
			EXPECT(RLEListMap(l, NULL) == RLE_LIST_NULL_ARGUMENT);

		TEST_CASE: RLEListDestory   
			EXPECT(RLEListRemove(NULL, 0) == RLE_LIST_NULL_ARGUMENT);

		TEST_CASE:
			EXPECT(RLEListRemove(l, 0) == RLE_LIST_INDEX_OUT_OF_BOUNDS);

	END_BLOCK

	TEST_BLOCK: General
		BEFORE_ALL:
			RLEList l;
			RLEListResult result;
		BEFORE_EACH:
			l = RLEListCreate();
			ASSERT((void*)l != __NULLPTR);
		AFTER_EACH:
			RLEListDestroy(l);

		TEST_BLOCK: RLEListGet
			EXPECT_ALL:
			TEST_CASE: Lower bound
				RLEListGet(l, -1, &result) == 0;
			TEST_CASE: Lower bound result
				result == RLE_LIST_INDEX_OUT_OF_BOUNDS;
			TEST_CASE: Upper bound
				RLEListGet(l, RLEListSize(l), &result) != 0;
			TEST_CASE: Upper bound result
				result != RLE_LIST_INDEX_OUT_OF_BOUNDS;
			TEST_CASE: Full get tests
				testRLEListGet("");
				testRLEListGet("abc");
				testRLEListGet("abbbbbbbcccc");
				testRLEListGet("aaaaaaaaaaaaaaaac");
			END_ALL:
		END_BLOCK
	END_BLOCK
END_BLOCK
