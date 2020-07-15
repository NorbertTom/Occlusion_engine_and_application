#pragma once

class NorMemoryPool;

class NorMemoryPoolChunk // used for one type of data
{
public:
	NorMemoryPoolChunk(NorMemoryPool* memoryPool, const unsigned int bytesPerObject, const unsigned int Quantity);
	~NorMemoryPoolChunk();

	void* addToPool(void* data);
	bool deleteFromPool(void* ptr);

private:
	const unsigned int c_bytesPerObject;
	const unsigned int c_quantity;
	void* c_chunkStartPtr = nullptr;
	inline void* chunkEndPtr() { return reinterpret_cast<char*>(c_chunkStartPtr) + (c_bytesPerObject * c_quantity); }
	bool* m_isSlotFree; // table of booleans

	int getNextFreeSlotPosition();
	void* getSlotPtr(const unsigned int position);
};

