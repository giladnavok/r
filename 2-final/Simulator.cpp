#include "Cache.h"
#include "Simulator.h"

Simulator::Simulator(uint MemCyc, uint BSize, uint L1Size, uint L2Size, uint L1Assoc, uint L2Assoc, uint L1Cyc, uint L2Cyc, uint WrAlloc) :
	m_top(new InputCache()),
	m_cacheLayers(),
	m_accessCount(),
	m_cycles() {
	Cache* L1 = new CacheLayer(L1Size, BSize, L1Assoc, L1Cyc, WrAlloc);
	m_top->setDown(L1);
	L1->setUp(m_top.get());
	Cache* L2 = new CacheLayer(L2Size, BSize, L2Assoc, L2Cyc, WrAlloc);
	L1->setDown(L2);
	L2->setUp(L1);
	Cache* mainMemory = new MainMemory(MemCyc, WrAlloc);
	L2->setDown(mainMemory);
	mainMemory->setUp(L2);
	m_cacheLayers.push_back(static_cast<CacheLayer*>(L1));
	m_cacheLayers.push_back(static_cast<CacheLayer*>(L2));
}

void Simulator::simulate(char operation, uint addr) {
	++m_accessCount;
	if (operation == 'r') {
		m_cycles += m_top->read(addr);
	} else {
		m_cycles += m_top->write(addr);
	}
}

 std::vector<double> Simulator::getStats() {
	std::vector<double> stats;
	for (CacheLayer* cache : m_cacheLayers) {
		stats.push_back(
			static_cast<double>(cache->getMissRate())
		);
	}
	stats.push_back(static_cast<double>(m_cycles) / m_accessCount);
	return stats;
}
	
	
	
	
