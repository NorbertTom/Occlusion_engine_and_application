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

private:
	void* m_startAddress = nullptr;
	void* m_endAddress = nullptr;
	void* m_nextFreeAddress = nullptr;
};

extern NorMemoryPool* norMemoryPool;