#include <stdbool.h>
#include "TestBlockTrace.h"
#include "Tree.h"

TestBlockTrace createTestBlockTrace() {
	TestBlockTrace ret = {
		.testBlocks = createArray(sizeof(TestBlock))
	};
	return ret;
}

void destroyTestBlockTrace(TestBlockTrace *trace) {
	destroyArray(&trace->testBlocks);
}

void pushTrace(TestBlockTrace* trace, TestBlock testBlock) {
	appendArray(&trace->testBlocks, &testBlock);
}

TestBlock popTrace(TestBlockTrace* trace) {
	return *((TestBlock*) popArray(&trace->testBlocks));
}

bool isTraceEmpty(const TestBlockTrace* trace) {
	return (trace->testBlocks.elementCount == 0);
}
