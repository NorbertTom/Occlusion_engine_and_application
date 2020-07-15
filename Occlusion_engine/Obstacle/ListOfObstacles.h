#pragma once
#include "SoundAPI.h"
#include "ListOfObstaclesInterface.h"

#include <vector>


class SOUND_API ListOfObstacles : public ListOfObstaclesInterface
{
public:
	
	ListOfObstacles();
	~ListOfObstacles();
	Obstacle* addObstacle(ObstacleDescriptor &obstacleDescriptor) override;
	void deleteObstacleById(int Id) override;
	void deleteObstacleByNr(int Nr) override;
	void deleteAll() override;
	
	Obstacle* getPtrById(int Id) const override;
	Obstacle* getPtrByNr(int Nr) const override;
	Obstacle* operator[] (int Nr) const override;
	
	int getObstaclesAmount() const override { return m_obstaclesAmount; };

private:
	std::vector<Obstacle*> m_listOfPointers;
	int m_nextId = 0;
	int m_obstaclesAmount = 0;

	int getListNrById(int Id) const;
};

extern SOUND_API ListOfObstacles* listOfObstaclesPtr;
//extern NorMemoryPoolChunk* obstaclesMemoryPool;