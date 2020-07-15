#pragma once

class Obstacle;

class ObstacleInterface
{
public:
	virtual int getId() const = 0;
	virtual float getDampening() const = 0;
	virtual void setPosition(float X1, float Y1, float X2, float Y2) = 0;
	virtual void setDampening(float newDampening) = 0;
	virtual void print() const = 0;
};