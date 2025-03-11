#ifndef TRACE_H
#define TRACE_H

#include "Array.h"
#include "Tree.h"

typedef struct TestBlockTrace {
	Array testBlocks;
} TestBlockTrace;

TestBlockTrace createTestBlockTrace();
void destroyTestBlockTrace(TestBlockTrace*);
void pushTrace(TestBlockTrace*, const TestBlock);
TestBlock popTrace(TestBlockTrace*);
bool isTraceEmpty(const TestBlockTrace*);

#endif // TRACE_H
