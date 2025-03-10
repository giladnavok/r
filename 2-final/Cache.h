#ifndef CACHE_H
#define CACHE_H
#include <vector>
#include <list>
#include <cstddef>

using uint = unsigned int;

constexpr bool DIRTY = true;
constexpr bool NOT_DIRTY = false;

class Cache {
public:
	Cache();
	virtual uint read(uint)=0;
	virtual uint write(uint)=0;
	virtual void insert(uint, bool);
	virtual void remove(uint);

	virtual void writeBack(uint);
	virtual void moveToFrontLRU(uint);

	virtual void setUp(Cache*);
	virtual void setDown(Cache*);
	virtual Cache* getDown();
	virtual ~Cache();
protected:
	Cache* m_up;
	Cache* m_down;
};

class InputCache : public Cache {
public:
	InputCache()=default;
	uint read(uint) override;
	uint write(uint) override;
	~InputCache()=default;
private:
};

class CacheLayer : public Cache {
public:
	CacheLayer(uint memorySize, uint blockSize, uint assocLevel, uint accessTime, uint writeAllocate);
	uint read(uint) override;
	uint write(uint) override;
	void insert(uint, bool) override;
	void remove(uint) override;
	void writeBack(uint) override;
	void moveToFrontLRU(uint) override;

	void setUp(Cache* cache) override;

	uint getMissCount();
	double getMissRate();

private:
	uint m_logMemorySize;
	uint m_logBlockSize;
	uint m_logAssocLevel;
	uint m_accessTime; // Counted in cycles
	bool m_writeAllocate;
	bool m_isTop;
	bool isTopCacheLayer();


	struct Entry {
		Entry()=default;
		uint tag;
		bool dirty;
		bool valid;
		bool operator==(const CacheLayer::Entry& other) {
			return tag == other.tag && valid == other.valid && dirty == other.dirty;
		}
	};

	struct Set {
		Set(uint size) : entries(size) {
			for (uint i = 0; i < size; ++i) {
				LRU.push_front(i);
				LRUNodes.push_back(LRU.begin());
			}
		}
		std::vector<Entry> entries;

		std::list<uint> LRU;
		std::vector<std::list<uint>::iterator> LRUNodes;

		int find(uint tag);
		uint getLastUsedEntryIndex();
		void moveToFrontLRU(uint blockIndex);
		void moveToSecondLRU(uint blockIndex);
		bool insertToInvalid(uint tag);
		Entry& getVictim();
		void invalidate(uint blockIndex);
		void dirty(uint blockIndex);
		Set& operator=(const Set&)=delete;
		Set(const Set& other) :
			entries(other.entries),
			LRU(other.LRU),
			LRUNodes(LRU.size()) {
			for (auto it = LRU.begin(); it != LRU.end(); ++it) {
				LRUNodes[*it] = it;
			}
		}
		void print();
	};

	std::vector<Set> m_sets;
	Set& getSet(uint addr);
	uint getSetIndex(uint addr);
	uint getTag(uint addr);


	static bool isValid(uint);
	static bool isDirty(uint);
	uint getAddressEntry(Entry&, uint);

	uint m_missCount;
	uint m_accessCount;

	~CacheLayer()=default;
};


class MainMemory : public Cache {
public:
	MainMemory(uint accessTime, uint writeAllocate);
	uint read(uint) override;
	uint write(uint) override;
	~MainMemory()=default;
private:
	uint m_accessTime;
	uint m_writeAllocate;
};
	

#endif // CACHE_H
