#include "NorMemoryPoolChunk.h"
#include <memory>
#include "NorMemoryPool.h"

NorMemoryPoolChunk::NorMemoryPoolChunk(NorMemoryPool* memoryPool, const unsigned int BytesPerObject, const unsigned int Quantity)
	: c_bytesPerObject(BytesPerObject), c_quantity(Quantity), c_bytesTotal(BytesPerObject*Quantity)
{
	c_chunkStartPtr = memoryPool->reserveMemory(c_bytesTotal);

	m_isSlotFree = new bool[c_quantity];
	for (unsigned int i = 0; i < c_quantity; i++)
	{
		m_isSlotFree[i] = true;
	}
}


NorMemoryPoolChunk::~NorMemoryPoolChunk()
{
	delete[] m_isSlotFree;
}

void* NorMemoryPoolChunk::addToPool(void* data)
{
	const unsigned int position = getNextFreeSlotPosition();
	if (void* destinationPtr = getSlotPtr(position))
	{
		memcpy(destinationPtr, data, c_bytesPerObject);
		m_isSlotFree[position] = false;
		m_bytesUsed = m_bytesUsed + c_bytesPerObject;
		return destinationPtr;
	}
	else
	{
		return nullptr; //no free memory slot
	}
}

bool NorMemoryPoolChunk::deleteFromPool(void* ptr)
{
	for (unsigned int i = 0; i < c_quantity; i++)
	{
		if (getSlotPtr(i) == ptr)
		{
			m_isSlotFree[i] = true;
			m_bytesUsed = m_bytesUsed - c_bytesPerObject;
			return true;
		}
	}
	return false; // can't find proper position in that chunk
}

void* NorMemoryPoolChunk::getSlotPtr(const unsigned int position)
{
	if (position < c_quantity)
	{
		return (reinterpret_cast<char*>(c_chunkStartPtr) + (c_bytesPerObject * position));
	}
	else
	{
		return nullptr; // no free slot
	}
}

int NorMemoryPoolChunk::getNextFreeSlotPosition()
{
	for (unsigned int i = 0; i < c_quantity; i++)
	{
		if (m_isSlotFree[i] == true)
		{
			return i;
		}
	}
	return c_quantity + 1; // no free slot
}