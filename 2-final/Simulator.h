#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <memory>
#include <vector>
#include "Cache.h"

using uint = unsigned int;

class Simulator {
public:
	Simulator(uint MemCyc, uint BSize, uint L1Size, uint L2Size, uint L1Assoc, uint L2Assoc, uint L1Cyc, uint L2Cyc, uint WrAlloc);
	void simulate(char operation, uint num);
	std::vector<double> getStats();
private:
	std::unique_ptr<InputCache> m_top;
	std::vector<CacheLayer*> m_cacheLayers;
	uint m_accessCount;
	uint m_cycles;
};


#endif // SIMULATOR_H
