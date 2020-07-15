#pragma once

#include "SoundAPI.h"
#include "ObstacleInterface.h"
#include "BaseClassesFunctions.h"

struct ObstacleDescriptor
{
	float m_x1 = 0;
	float m_y1 = 0;
	float m_x2 = 0;
	float m_y2 = 0;
	float m_damp = 20;
	int m_id = 0;

	ObstacleDescriptor(float x1, float y1, float x2, float y2, float damp, int id)
		: m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_damp(damp), m_id(id) {};

	ObstacleDescriptor(float x1, float y1, float x2, float y2, float damp)
		: m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_damp(damp), m_id(0) {};

	ObstacleDescriptor() {};
	~ObstacleDescriptor() {};
};

class ListOfObstacles;

class SOUND_API Obstacle : public BasicMath::TwoPoints, public ObstacleInterface
{
public:

	int getId() const override { return m_id; }
	float getDampening() const override { return m_dampening; };
	void setPosition(float X1, float Y1, float X2, float Y2) override;
	void setDampening(float newDampening) override;
	void print() const override;	
	BasicMath::Line ObstacleLine() const;

	bool operator== (Obstacle& const otherObstacle) const;

	static const int memoryPerObject = 5*sizeof(float);
	
private:

	int m_id;
	float m_dampening;
	
	Obstacle(ObstacleDescriptor& obstacleDescriptor);
	~Obstacle();

	friend class ListOfObstacles;
};