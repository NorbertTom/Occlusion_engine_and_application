#include "ListOfReceivers.h"
#include "Receiver.h"
#include "ErrorLogging.h"

#include "NorMemoryPool.h"
#include "NorMemoryPoolChunk.h"

ListOfReceivers* listOfReceiversPtr = new ListOfReceivers();

#ifdef UsingNorMemoryPool
NorMemoryPoolChunk* receiversMemoryPool = new NorMemoryPoolChunk(norMemoryPool, sizeof(Receiver), 20); // ?? test fails because of 20 limit
#endif


ListOfReceivers::ListOfReceivers()
{
#ifdef UsingNorMemoryPool
	// ----
#else
	m_listOfPointers.reserve(5);
#endif
}

ListOfReceivers::~ListOfReceivers()
{
	deleteAll();
}

Receiver* ListOfReceivers::createReceiver(float X, float Y)
{
	deactivateAll();

#ifdef UsingNorMemoryPool
	Receiver newReceiverStack(X, Y, m_nextId);
	auto allocator = receiversMemoryPool->addToPool(&newReceiverStack);
	if (!allocator)
	{
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
	if (nr == 2000000)
	{
		LOG_WARNING("Wrong Id provided in deleteReceiverById method!");
		return;
	}
	deleteReceiverByNr(nr);
}

void ListOfReceivers::deleteReceiverByNr(int Nr)
{
#ifdef UsingNorMemoryPool
	receiversMemoryPool->deleteFromPool(m_listOfPointers[Nr]);
#else
	delete m_listOfPointers[Nr];
#endif

	auto it = m_listOfPointers.begin();
	m_listOfPointers.erase(it + Nr);
	m_receiversAmount--;
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
		if (activePtr==m_listOfPointers[iterator])
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
		if (m_listOfPointers[i]->ifActive())
		{
			activePtr = m_listOfPointers[i];
			return activePtr; // for performance sake
		}
	}
	return activePtr;
}

Receiver* ListOfReceivers::operator[](int Nr) const
{
	if (Nr < m_receiversAmount)
	{
		return m_listOfPointers[Nr];
	}
	else
	{
		return nullptr;
	}
}

int ListOfReceivers::getReceiversAmount() const
{
	return m_receiversAmount;
}

int ListOfReceivers::getListNrById(int Id) const
{
	for (int i = 0; i < m_receiversAmount; i++)
	{
		if (m_listOfPointers[i]->getId() == Id)
		{
			return i;
		}
	}
	LOG_ERROR("Didn't find object by id in ListOfSources::getListNrById!");
	return 2000000;
}

Receiver* ListOfReceivers::getPtrByNr(int Nr) const
{
	if (Nr < m_receiversAmount)
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
		if (m_listOfPointers[i]->getId() == id)
		{
			return m_listOfPointers[i];
		}
	}
	return nullptr;
}

void ListOfReceivers::activate(int nr) const
{
	if (nr < m_receiversAmount)
	{
		deactivateAll();
		m_listOfPointers[nr]->activate();
	}
}

void ListOfReceivers::activateById(int id) const
{
	deactivateAll();
	getPtrById(id)->activate();
}

void ListOfReceivers::deactivateAll() const
{
	for (int i = 0; i < m_receiversAmount; i++)
	{
		m_listOfPointers[i]->deactivate();
	}
}