#include "ListOfObstacles.h"
#include "Obstacle.h"
#include "ErrorLogging.h"
#include "NorMemoryPool.h"
#include "NorMemoryPoolChunk.h"
#include "PerformanceDefines.h"

#ifdef ObstaclesUsingNorMemoryPool
	SOUND_API NorMemoryPoolChunk* obstaclesMemoryPool = new NorMemoryPoolChunk(norMemoryPool, sizeof(Obstacle), 50);
	static const int limit = 50;
#else
	SOUND_API NorMemoryPoolChunk* obstaclesMemoryPool = nullptr;
	static const int limit = 1000;
#endif

ListOfObstacles* listOfObstaclesPtr = new ListOfObstacles();

ListOfObstacles::ListOfObstacles() : m_obstaclesAmountLimit(limit)
{
#ifdef ObstaclesUsingNorMemoryPool
	// reserve memory from pool
#else
	m_listOfPointers.reserve(10);
#endif
}

ListOfObstacles::~ListOfObstacles()
{
	deleteAll();

#ifdef ObstaclesUsingNorMemoryPool
	delete obstaclesMemoryPool;
#endif
}

Obstacle* ListOfObstacles::addObstacle(ObstacleDescriptor& obstacleDescriptor)
{
	obstacleDescriptor.m_id = m_nextId;

#ifdef ObstaclesUsingNorMemoryPool
	Obstacle newObstacleStack(obstacleDescriptor);
	auto allocator = obstaclesMemoryPool->addToPool(&newObstacleStack);
	if (!allocator)
	{
		LOG_WARNING("No obstacle added, memory full");
		return nullptr;
	}
	Obstacle* newObstacle = reinterpret_cast<Obstacle*>(allocator); 
#else
	Obstacle* newObstacle = new Obstacle(obstacleDescriptor);
#endif

	m_listOfPointers.push_back(newObstacle);
	m_nextId++;
	m_obstaclesAmount++;
	return newObstacle;
}

void ListOfObstacles::deleteObstacleById(int Id)
{
	int number = getListNrById(Id);
	if (number == -1)
	{
		LOG_ERROR("Wrong ID provided in deleteObstacleById");
	}
	else
	{
		deleteObstacleByNr(number);
	}
}

void ListOfObstacles::deleteObstacleByNr(int Nr)
{
	if (isListIndexValid(Nr))
	{
#ifdef ObstaclesUsingNorMemoryPool
		obstaclesMemoryPool->deleteFromPool(m_listOfPointers[Nr]);
#else
		delete m_listOfPointers[Nr];
#endif

		auto it = m_listOfPointers.begin();
		m_listOfPointers.erase(it + Nr);
		m_obstaclesAmount--;
	}
}

void ListOfObstacles::deleteAll()
{
	while (m_obstaclesAmount > 0)
	{
		deleteObstacleByNr(0);
	}
	m_nextId = 0;
}

Obstacle* ListOfObstacles::getPtrByNr(int Nr) const
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

Obstacle* ListOfObstacles::getPtrById(int Id) const
{
	for (int i = 0; i < m_obstaclesAmount; i++)
	{
		if (getPtrByNr(i) && getPtrByNr(i)->getId() == Id)
		{
			return m_listOfPointers[i];
		}
	}
	return nullptr;
}

int ListOfObstacles::getListNrById(int Id) const
{
	for (int i = 0; i < m_obstaclesAmount; i++)
	{
		if (getPtrByNr(i) && getPtrByNr(i)->getId() == Id)
		{
			return i;
		}
	}
	LOG_WARNING("Didn't find object by ID in ListOfObstacles::getListNrById!");
	return -1;
}

Obstacle* ListOfObstacles::operator[] (int Nr) const
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

bool ListOfObstacles::isListIndexValid(int Nr) const
{
	bool result = false;
	if (Nr < m_listOfPointers.size() && Nr > -1)
	{
		result = true;
	}
	return result;
}