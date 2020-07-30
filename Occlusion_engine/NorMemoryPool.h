#pragma once

#define UsingNorMemoryPool

class NorMemoryPoolChunk;

class NorMemoryPool
{
public:
	void* reserveMemory(const unsigned int memoryAmount);
	// Doesn't have freeMemory function because it only gives memory to MemoryPoolChunks on initialization
	NorMemoryPool(const unsigned int memoryAmount);
	~NorMemoryPool();

	void* getNextFreeAddress() const { return m_nextFreeAddress; }
	static const int c_bytesCapacity = 6000;

private:
	void* m_startAddress = nullptr;
	void* m_endAddress = nullptr;
	void* m_nextFreeAddress = nullptr;
	unsigned int m_bytesReserved = 0;
};

extern NorMemoryPool* norMemoryPool;