#include "Obstacle.h"
#include "ErrorLogging.h"

Obstacle::Obstacle(ObstacleDescriptor& obstacleDescriptor)
	: BasicMath::TwoPoints(obstacleDescriptor.m_x1, obstacleDescriptor.m_y1, obstacleDescriptor.m_x2, obstacleDescriptor.m_y2),
		m_dampening(obstacleDescriptor.m_damp), m_id(obstacleDescriptor.m_id)
{
}


Obstacle::~Obstacle()
{
}

BasicMath::Line Obstacle::ObstacleLine() const
{ // czemu to osobna metoda? Nie mo¿e siê robiæ gdizeœ indziej?
	// X1, Y1, X2 i Y2 mog³yby zostaæ przekazane jako parametry?
	BasicMath::Line line((getPosY1() - getPosY2()) / (getPosX1() - getPosX2()), getPosY2() - 
		(getPosX2()*(getPosY1() - getPosY2()) / (getPosX1() - getPosX2())));
	return line;
}


void Obstacle::setPosition(float X1, float Y1, float X2, float Y2)
{
	setPosX1(X1);
	setPosY1(Y1);
	setPosX2(X2);
	setPosY2(Y2);
}

void Obstacle::setDampening(float newDampening)
{
	m_dampening = newDampening;
}

void Obstacle::print() const
{
	std::cout << "Obstacle ID: " << m_id << ", P1(" << getPosX1() << ", " << getPosY1() << "); P2(" 
		<< getPosX2() << ", " << getPosY2() << "); dampening = " << m_dampening << "dB\n";
}

bool Obstacle::operator== (Obstacle& const otherObstacle) const
{
	bool result = false;
	if (this->getPosX1() == otherObstacle.getPosX1())
	{
		if (this->getPosY1() == otherObstacle.getPosY1())
		{
			if (this->getPosX2() == otherObstacle.getPosX2())
			{
				if (this->getPosY2() == otherObstacle.getPosY2())
				{
					if (this->getDampening() == otherObstacle.getDampening())
					{
						result = true;
					}
				}
			}
		}
	}
	return result;
}