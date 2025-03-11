#include "RLEList.h" // Sourced from second file

TEST_BLOCK: RLEList.h
	TEST_BLOCK: General
		TEST_BLOCK: RLEListAppend
			TEST_CASE: Append
				RLEListAppend(l, 'a');
				RLEListAppend(l, 'b');
				for (int i = 0; i < 5; i++) {
					RLEListAppend(l, 'a');
				}
				ASSERT(testList(l, "a1\nb1\na5\n", 7));

			TEST_CASE: Append many
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
		END_BLOCK
	END_BLOCK
END_BLOCK

TEST_BLOCK: RLEList.h from second file
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
