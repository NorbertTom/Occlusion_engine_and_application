#include "NorMemoryPool.h"
#include <memory>

NorMemoryPool* norMemoryPool = new NorMemoryPool(50000);

NorMemoryPool::NorMemoryPool(const unsigned int memoryAmount)
{
	if (m_startAddress = malloc(memoryAmount))
	{
		m_endAddress = reinterpret_cast<char*>(m_startAddress) + memoryAmount;
		m_nextFreeAddress = m_startAddress;
	}
	else
	{
		// ERROR, Can't reserve memory for some reason
	}
}

NorMemoryPool::~NorMemoryPool()
{
	free(m_startAddress);
}

void* NorMemoryPool::reserveMemory(const unsigned int memoryAmount)
{
	void* pointerToReturn = nullptr;
	if (reinterpret_cast<char*>(m_nextFreeAddress) + memoryAmount > reinterpret_cast<char*>(m_endAddress))
	{
		// ERROR, not enough memory
		return pointerToReturn;
	}
	pointerToReturn = m_nextFreeAddress;
	m_nextFreeAddress = reinterpret_cast<char*>(m_nextFreeAddress) + memoryAmount;
	return pointerToReturn;
}