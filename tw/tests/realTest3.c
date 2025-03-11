#include "RLEList.h" // Sourced from third file

TEST_BLOCK: RLEList.h
	TEST_BLOCK: General
		TEST_BLOCK: RLEListGet from third file
			TEST_CASE: Lower bound
				EXPECT(RLEListGet(l, -1, &result) == 0);
			TEST_CASE: Lower bound result
				EXPECT(result == RLE_LIST_INDEX_OUT_OF_BOUNDS);
			TEST_CASE: Upper bound
				EXPECT(RLEListGet(l, RLEListSize(l), &result) != 0) ;
			TEST_CASE: Upper bound result
				EXPECT(result != RLE_LIST_INDEX_OUT_OF_BOUNDS);
			TEST_CASE: Full get tests
				// STARTS HERE
				EXPECT_ALL:
				testRLEListGet("");
				testRLEListGet("abc");
				testRLEListGet("abbbbbbbcccc");
				testRLEListGet("aaaaaaaaaaaaaaaac");
				END_EXPECT_ALL:
				
				// ENDS  HERE
		END_BLOCK
	END_BLOCK
END_BLOCK

TEST_BLOCK: RLEList.h from third file
	TEST_BLOCK: General
		BEFORE_ALL:
			RLEList l;
			RLEListResult result;
		BEFORE_EACH:
			l = RLEListCreate();
			ASSERT((void*)l != __NULLPTR);
		AFTER_EACH:
			RLEListDestroy(l);

		TEST_BLOCK: RLEListGet from third file
			TEST_CASE: Lower bound
				EXPECT(RLEListGet(l, -1, &result) == 0);
			TEST_CASE: Lower bound result
				EXPECT(result == RLE_LIST_INDEX_OUT_OF_BOUNDS);
			TEST_CASE: Upper bound
				EXPECT(RLEListGet(l, RLEListSize(l), &result) != 0) ;
			TEST_CASE: Upper bound result
				EXPECT(result != RLE_LIST_INDEX_OUT_OF_BOUNDS);
			TEST_CASE: Full get tests
				EXPECT(testRLEListGet(""));
				EXPECT(testRLEListGet("abc"));
				EXPECT(testRLEListGet("abbbbbbbcccc"));
				EXPECT(testRLEListGet("aaaaaaaaaaaaaaaac"));
		END_BLOCK
	END_BLOCK
END_BLOCK
