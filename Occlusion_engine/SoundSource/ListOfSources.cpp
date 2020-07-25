#include "ListOfSources.h"

#include "ErrorLogging.h"
#include "SoundSource.h"
#include "NorMemoryPool.h"
#include "NorMemoryPoolChunk.h"

ListOfSources* listOfSourcesPtr = new ListOfSources();

#ifdef UsingNorMemoryPool
NorMemoryPoolChunk* sourcesMemoryPool = new NorMemoryPoolChunk(norMemoryPool, sizeof(SoundSource), 70); // ?? test fails because of 70 limit
#endif

ListOfSources::ListOfSources()
{
#ifdef UsingNorMemoryPool
	// memory pool operations
#else
	m_listOfPointers.reserve(10);
#endif
}

ListOfSources::~ListOfSources()
{
	deleteAll();

#ifdef UsingNorMemoryPool
	delete sourcesMemoryPool;
#endif
}

SoundSource* ListOfSources::addSource(SoundSourceDescriptor &soundSourceDescriptor)
{
	soundSourceDescriptor.m_id = m_nextId;

#ifdef UsingNorMemoryPool
	SoundSource newSourceStack(soundSourceDescriptor);
	auto allocator = sourcesMemoryPool->addToPool(&newSourceStack);
	if (!allocator)
	{
		return nullptr;
	}
	SoundSource* newSource = reinterpret_cast<SoundSource*>(allocator);
#else
	SoundSource* newSource = new SoundSource(soundSourceDescriptor);
#endif

	m_listOfPointers.push_back(newSource);
	m_nextId++;
	m_sourcesAmount++;
	return newSource;
}

void ListOfSources::deleteSourceById(int Id)
{
	int number = getListNrById(Id);
	if (number == 2000000)
	{
		LOG_ERROR("Wrong ID provided in deleteSourceById");
	}
	else
	{
		deleteSourceByNr(number);
	}
}

void ListOfSources::deleteSourceByNr(int Nr) //should be crash proofed if (Nr < m_sourcesAmount) or smth
{
#ifdef UsingNorMemoryPool
	sourcesMemoryPool->deleteFromPool(m_listOfPointers[Nr]);
#else
	delete m_listOfPointers[Nr];
#endif

	auto it = m_listOfPointers.begin();
	m_listOfPointers.erase(it + Nr);
	m_sourcesAmount--;
}

void ListOfSources::deleteAll()
{
	while (m_sourcesAmount > 0)
	{
		deleteSourceByNr(0);
	}
	m_nextId = 0;
}

SoundSource* ListOfSources::getPtrById(int Id) const
{
	for (int i = 0; i < m_sourcesAmount; i++)
	{
		if (m_listOfPointers[i]->getId() == Id)
		{
			return m_listOfPointers[i];
		}
	}
	return nullptr;
}

SoundSource* ListOfSources::getPtrByNr(int Nr) const
{
	if (Nr < m_sourcesAmount)
	{
		return m_listOfPointers[Nr];
	}
	else
	{
		return nullptr;
	}
}

int ListOfSources::getListNrById(int Id) const
{
	for (int i = 0; i < m_sourcesAmount; i++)
	{
		if (m_listOfPointers[i]->getId() == Id)
		{
			return i;
		}
	}
	LOG_WARNING("Didnt find object by ID in ListOfSources::getListNrById!");
	return 2000000;
}

SoundSource* ListOfSources::operator[] (int Nr) const
{
	if (Nr < m_sourcesAmount)
	{
		return m_listOfPointers[Nr];
	}
	else
	{
		return nullptr;
	}
}