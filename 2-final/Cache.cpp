#include <cmath>
#include <vector>
#include <cstddef>
#include <cassert>
#include <list>
#include <algorithm>
#include <iostream>
#include <memory>
#include "Cache.h"

CacheLayer::CacheLayer(uint logMemorySize, uint logBlockSize, uint logAssocLevel, uint accessTime, uint writeAllocate) :
	m_logMemorySize(logMemorySize),
	m_logBlockSize(logBlockSize),
	m_logAssocLevel(logAssocLevel),
	m_accessTime(accessTime),
	m_writeAllocate(writeAllocate),
	m_isTop(),
	m_missCount(),
	m_accessCount() {

	int logNumBlocks = logMemorySize - logBlockSize;
	int logNumSets = logNumBlocks - logAssocLevel;
	int numSets = pow(2, logNumSets);
	int numWays = pow(2, logAssocLevel);
	for (int i = 0; i < numSets; ++i) {
		m_sets.emplace_back(numWays);
	}
}


uint CacheLayer::read(uint addr) {
	// Log access 
	++m_accessCount;
	// Check if the given address is stored in this cache
	Set &set = getSet(addr);
	int entryIndex = set.find(getTag(addr));

	if (entryIndex != -1) { // Hit
		set.moveToFrontLRU(entryIndex);
		if (!isTopCacheLayer()) {
			m_up->insert(addr, NOT_DIRTY);
		}
		return m_accessTime;
	}  // Miss
	
	++m_missCount;
	return m_accessTime + m_down->read(addr);
}

uint CacheLayer::write(uint addr) {
	// Log access 
	++m_accessCount;
	// Check if the given address is stored in this cache
	Set &set = getSet(addr);
	int entryIndex = set.find(getTag(addr));

	if (entryIndex != -1) { // Hit
		set.moveToFrontLRU(entryIndex);
		if (!isTopCacheLayer() && m_writeAllocate) {
			m_up->insert(addr, DIRTY);
		} else {
			set.dirty(entryIndex);
		}
		return m_accessTime; 
	} // Miss

	++m_missCount;
	return m_accessTime + m_down->write(addr);
	
}

void CacheLayer::insert(uint addr, bool isDirty) {
	Set &set = getSet(addr);
	int entryIndex = set.find(getTag(addr));
	if (entryIndex == -1) {
		CacheLayer::Entry& toRemoveEntry = set.getVictim();
		if (toRemoveEntry.valid) {
			uint removedAddress = getAddressEntry(toRemoveEntry, getSetIndex(addr));
			assert(getTag(removedAddress) == toRemoveEntry.tag);
			remove(removedAddress);
		}
		set.insertToInvalid(getTag(addr));
	}

	if (isTopCacheLayer() && isDirty) {
		entryIndex = set.find(getTag(addr));
		set.dirty(entryIndex);
	}
	m_up->insert(addr, isDirty);
}

void CacheLayer::writeBack(uint addr) {
	Set &set = getSet(addr);
	int entryIndex = set.find(getTag(addr));
	if (entryIndex != -1) {
		set.dirty(entryIndex);
		set.moveToFrontLRU(entryIndex);

	} else {
		assert(0);
		m_down->writeBack(addr);
	}
}

void CacheLayer::remove(uint addr) {
	Set &set = getSet(addr);
	int entryIndex = set.find(getTag(addr));
	if (entryIndex == -1) {
		return;
	}

	m_up->remove(addr);

	set.invalidate(entryIndex);
	if (set.entries[entryIndex].dirty) {
		m_down->writeBack(addr);
	} 
}


CacheLayer::Set& CacheLayer::getSet(uint addr) {
	return m_sets[getSetIndex(addr)];
}

uint CacheLayer::getTag(uint addr) {
	uint nonTagSize = (m_logBlockSize + m_logMemorySize - m_logBlockSize - m_logAssocLevel);
	int tag = addr >> nonTagSize;
	tag <<= nonTagSize;
	return tag;
}

bool CacheLayer::isValid(uint addr) {
	return (addr & 1);
}

bool CacheLayer::isDirty(uint addr) {
	return (addr & 2);
}

uint CacheLayer::getAddressEntry(CacheLayer::Entry& entry, uint setIndex) {
	return entry.tag + (setIndex << m_logBlockSize);
}

uint CacheLayer::getSetIndex(uint addr) {
	return (addr - getTag(addr)) >> m_logBlockSize;
}

int CacheLayer::Set::find(uint tag) {
	for (uint i = 0; i < entries.size(); ++i) {
		if (entries[i].valid && (entries[i].tag == tag)) {
			return i;
		}
	}
	return -1;
}

uint CacheLayer::Set::getLastUsedEntryIndex() {
	return LRU.back();
}
	
void CacheLayer::Set::moveToFrontLRU(uint entryIndex) {
	assert(entryIndex != -1);
	LRU.erase(LRUNodes[entryIndex]);
	LRU.push_front(entryIndex);
	LRUNodes[entryIndex] = LRU.begin();
}

void CacheLayer::Set::moveToSecondLRU(uint entryIndex) {
	assert(entryIndex != -1);
	LRU.erase(LRUNodes[entryIndex]);
	LRU.insert(std::next(LRU.begin(), 1), entryIndex);
	LRUNodes[entryIndex] = std::next(LRU.begin(), 1);
}

void CacheLayer::Set::invalidate(uint entryIndex) {
	entries[entryIndex].valid = false;
}

void CacheLayer::Set::dirty(uint entryIndex) {
	entries[entryIndex].dirty = true;
}

bool CacheLayer::Set::insertToInvalid(uint tag) {
	Entry &entry = getVictim();
	assert(entry.valid == false);
	entry.tag = tag;
	entry.dirty = false;
	entry.valid = true;
	moveToFrontLRU((std::find(entries.begin(), entries.end(), entry)) - entries.begin());
	return true;
}

CacheLayer::Entry& CacheLayer::Set::getVictim() {
	return entries[LRU.back()];
}

uint CacheLayer::getMissCount() {
	return m_missCount;
}

double CacheLayer::getMissRate() {
	return static_cast<double>(m_missCount)/m_accessCount;
}

void CacheLayer::moveToFrontLRU(uint addr) {
	Set &set = getSet(addr);
	int entryIndex = set.find(getTag(addr));
	if (entryIndex == -1) {
		return;
	}
	set.moveToFrontLRU(entryIndex);
	m_down->moveToFrontLRU(addr);
}

bool CacheLayer::isTopCacheLayer() {
	return m_isTop;
}
	
Cache::Cache() :
	m_up(), m_down() {}

Cache::~Cache() {
	if (m_down != nullptr) {
		delete m_down;
	}
}

void Cache::setUp(Cache* cache) {
	m_up = cache;
}

void CacheLayer::setUp(Cache* cache) {
	m_up = cache;
	m_isTop = (dynamic_cast<CacheLayer*>(cache) == nullptr);
}

void Cache::setDown(Cache* cache) {
	m_down = cache;
}

void Cache::moveToFrontLRU(uint addr) {
	return;
}

Cache* Cache::getDown() {
	return m_down;
}

void Cache::insert(uint addr, bool) {
	return;
}

void Cache::remove(uint addr) {
	return;
}

void Cache::writeBack(uint addr) {}

uint InputCache::read(uint addr) {
	return m_down->read(addr);
}

uint InputCache::write(uint addr) {
	return m_down->write(addr);
}


MainMemory::MainMemory(uint accessTime, uint writeAllocate) :
	m_accessTime(accessTime),
	m_writeAllocate(writeAllocate) {}

uint MainMemory::read(uint addr) {
	m_up->insert(addr, NOT_DIRTY);
	return m_accessTime;
}

uint MainMemory::write(uint addr) {
	if (m_writeAllocate) {
		m_up->insert(addr, DIRTY);
	}
	return m_accessTime;
}


