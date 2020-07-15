#pragma once

class Obstacle;
struct ObstacleDescriptor;


class ListOfObstaclesInterface
{
public:
	virtual Obstacle* addObstacle(ObstacleDescriptor &obstacleDescriptor) = 0;
	virtual void deleteObstacleById(int Id) = 0;
	virtual void deleteObstacleByNr(int Nr) = 0;
	virtual void deleteAll() = 0;

	virtual Obstacle* getPtrById(int Id) const = 0;
	virtual Obstacle* getPtrByNr(int Nr) const = 0;
	virtual Obstacle* operator[] (int Nr) const = 0;

	virtual int getObstaclesAmount() const = 0;
};