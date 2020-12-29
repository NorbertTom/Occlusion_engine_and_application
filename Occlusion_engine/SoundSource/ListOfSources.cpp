#include "ListOfSources.h"
#include "SoundSource.h"
#include "ErrorLogging.h"
#include "NorMemoryPool.h"
#include "NorMemoryPoolChunk.h"

#define UsingNorMemoryPool // <- comment this line out if you do not want to use NorMemoryPool

#ifdef UsingNorMemoryPool
	SOUND_API NorMemoryPoolChunk* sourcesMemoryPool = new NorMemoryPoolChunk(norMemoryPool, sizeof(SoundSource), 70);
	static const int limit = 70;
#else
	SOUND_API NorMemoryPoolChunk* sourcesMemoryPool = nullptr;
	static const int limit = 1000;
#endif

ListOfSources* listOfSourcesPtr = new ListOfSources();


ListOfSources::ListOfSources() : m_sourcesAmountLimit(limit)
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
		return nullptr; // no free slot
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
	if (number == -1)
	{
		LOG_ERROR("Wrong ID provided in deleteSourceById");
	}
	else
	{
		deleteSourceByNr(number);
	}
}

void ListOfSources::deleteSourceByNr(int Nr)
{
	if (isListIndexValid(Nr))
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
	if (isListIndexValid(Nr))
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
	return -1;
}

SoundSource* ListOfSources::operator[] (int Nr) const
{
	if (isListIndexValid(Nr))
	{
		return m_listOfPointers[Nr];
	}
	else
	{
		return nullptr;
	}
}

bool ListOfSources::isListIndexValid(int Nr) const
{
	bool result = false;
	if (Nr < m_listOfPointers.size() && Nr > -1)
	{
		result = true;
	}
	return result;
}