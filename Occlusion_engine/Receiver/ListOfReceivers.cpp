#include "ListOfReceivers.h"
#include "Receiver.h"
#include "ErrorLogging.h"
#include "NorMemoryPool.h"
#include "NorMemoryPoolChunk.h"
#include "PerformanceDefines.h"

#ifdef ReceiversUsingNorMemoryPool
	SOUND_API NorMemoryPoolChunk* receiversMemoryPool = new NorMemoryPoolChunk(norMemoryPool, sizeof(Receiver), 20);
	static const int limit = 20;
#else
	SOUND_API NorMemoryPoolChunk* receiversMemoryPool = nullptr;
	static const int limit = 1000;
#endif

ListOfReceivers* listOfReceiversPtr = new ListOfReceivers();

ListOfReceivers::ListOfReceivers() : m_receiversAmountLimit(limit)
{
#ifdef ReceiversUsingNorMemoryPool
	// ----
#else
	m_listOfPointers.reserve(5);
#endif
}

ListOfReceivers::~ListOfReceivers()
{
	deleteAll();

#ifdef ReceiversUsingNorMemoryPool
	delete receiversMemoryPool;
#endif
}

Receiver* ListOfReceivers::createReceiver(float X, float Y)
{
	deactivateAll();

#ifdef ReceiversUsingNorMemoryPool
	Receiver newReceiverStack(X, Y, m_nextId);
	auto allocator = receiversMemoryPool->addToPool(&newReceiverStack);
	if (!allocator)
	{
		LOG_WARNING("No receiver added, memory full");
		return nullptr;
	}
	Receiver* newReceiver = reinterpret_cast<Receiver*>(allocator);

#else 
	Receiver* newReceiver = new Receiver(X, Y, m_nextId);
#endif

	m_listOfPointers.push_back(newReceiver);
	m_nextId++;
	m_receiversAmount++;
	return newReceiver;
}

void ListOfReceivers::deleteReceiverById(int Id)
{
	int nr = getListNrById(Id);
	if (nr == -1)
	{
		LOG_WARNING("Wrong Id provided in deleteReceiverById method!");
		return;
	}
	deleteReceiverByNr(nr);
}

void ListOfReceivers::deleteReceiverByNr(int Nr)
{
	if (isListIndexValid(Nr))
	{
#ifdef ReceiversUsingNorMemoryPool
		receiversMemoryPool->deleteFromPool(m_listOfPointers[Nr]);
#else
		delete m_listOfPointers[Nr];
#endif

		auto it = m_listOfPointers.begin();
		m_listOfPointers.erase(it + Nr);
		m_receiversAmount--;
	}
}

void ListOfReceivers::deleteAll()
{
	while (m_receiversAmount>0)
	{
		deleteReceiverByNr(0);
	}
	m_nextId = 0;
}

void ListOfReceivers::deleteAllButActive()
{
	Receiver* activePtr = getActive();
	int iterator = 0;
	while (m_receiversAmount > 1)
	{
		if (activePtr && activePtr==m_listOfPointers[iterator])
		{
			iterator++;
		}
		else
		{
			deleteReceiverByNr(iterator);
		}
	}
}

Receiver* ListOfReceivers::getActive() const
{
	Receiver* activePtr = nullptr;
	for (int i = 0; i < m_receiversAmount; i++)
	{
		if (getPtrByNr(i)->ifActive())
		{
			activePtr = m_listOfPointers[i];
			return activePtr; // for performance sake
		}
	}
	return activePtr;
}

Receiver* ListOfReceivers::operator[](int Nr) const
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

int ListOfReceivers::getListNrById(int Id) const
{
	for (int i = 0; i < m_receiversAmount; i++)
	{
		if (getPtrByNr(i) && getPtrByNr(i)->getId() == Id)
		{
			return i;
		}
	}
	LOG_ERROR("Didn't find object by id in ListOfSources::getListNrById!");
	return -1;
}

Receiver* ListOfReceivers::getPtrByNr(int Nr) const
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

Receiver* ListOfReceivers::getPtrById(int id) const
{
	for (int i = 0; i < m_receiversAmount; i++)
	{
		if (getPtrByNr(i) && getPtrByNr(i)->getId() == id)
		{
			return m_listOfPointers[i];
		}
	}
	return nullptr;
}

void ListOfReceivers::activate(int nr) const
{
	if (Receiver* receiverPtr = getPtrByNr(nr))
	{
		deactivateAll();
		receiverPtr->activate();
	}
}

void ListOfReceivers::activateById(int id) const
{
	if (Receiver* receiverPtr = getPtrById(id))
	{
		deactivateAll();
		receiverPtr->activate();
	}
}

void ListOfReceivers::deactivateAll() const
{
	for (int i = 0; i < m_receiversAmount; i++)
	{
		if (getPtrByNr(i))
		{
			getPtrByNr(i)->deactivate();
		}
	}
}

bool ListOfReceivers::isListIndexValid(int Nr) const
{
	bool result = false;
	if (Nr < m_listOfPointers.size() && Nr > -1)
	{
		result = true;
	}
	return result;
}