#include "ListOfObstacles.h"
#include "Obstacle.h"
#include "ErrorLogging.h"

#include "NorMemoryPool.h"
#include "NorMemoryPoolChunk.h"

ListOfObstacles* listOfObstaclesPtr = new ListOfObstacles();

#ifdef UsingNorMemoryPool
NorMemoryPoolChunk* obstaclesMemoryPool = new NorMemoryPoolChunk(norMemoryPool, sizeof(Obstacle), 50); // test fails because of 50 limit
#endif

ListOfObstacles::ListOfObstacles()
{
#ifdef UsingNorMemoryPool
	// reserve memory from pool
#else
	m_listOfPointers.reserve(10);
#endif
}

ListOfObstacles::~ListOfObstacles()
{
	deleteAll();

#ifdef UsingNorMemoryPool
	delete obstaclesMemoryPool;
#endif
}

Obstacle* ListOfObstacles::addObstacle(ObstacleDescriptor& obstacleDescriptor)
{
	obstacleDescriptor.m_id = m_nextId;

#ifdef UsingNorMemoryPool
	Obstacle newObstacleStack(obstacleDescriptor);
	auto allocator = obstaclesMemoryPool->addToPool(&newObstacleStack);
	if (!allocator)
	{
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
	if (number == 2000000)
	{
		LOG_ERROR("Wrong ID provided in deleteObstacleById");
	}
	else
	{
		deleteObstacleByNr(number);
	}
}

void ListOfObstacles::deleteObstacleByNr(int Nr) // nr should be crash proof here
{
#ifdef UsingNorMemoryPool
	obstaclesMemoryPool->deleteFromPool(m_listOfPointers[Nr]);
#else
	delete m_listOfPointers[Nr];
#endif

	auto it = m_listOfPointers.begin();
	m_listOfPointers.erase(it + Nr);
	m_obstaclesAmount--;
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
	if (Nr < m_obstaclesAmount)
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
		if (m_listOfPointers[i]->getId() == Id)
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
		if (m_listOfPointers[i]->getId() == Id)
		{
			return i;
		}
	}
	LOG_WARNING("Didn't find object by ID in ListOfObstacles::getListNrById!");
	return 2000000;
}

Obstacle* ListOfObstacles::operator[] (int Nr) const
{
	if (Nr < m_obstaclesAmount)
	{
		return m_listOfPointers[Nr];
	}
	else
	{
		return nullptr;
	}
}