#include "Receiver.h"

#include "ErrorLogging.h"


Receiver::~Receiver()
{
}

Receiver::Receiver(float X, float Y, int Id) : BasicMath::Point(X, Y), m_isActive(true), m_id(Id)
{
}

int Receiver::getId() const
{
	return m_id;
}

bool Receiver::ifActive() const
{
	return m_isActive;
}

void Receiver::moveReceiver(MoveReceiverDirection direction)
{
	float x = getPosX();
	float y = getPosY();
	float addX = 0;
	float addY = 0;

	switch (direction)
	{
	case MoveReceiverDirection::Up:
		addY = 1;
		break;
	case MoveReceiverDirection::Left:
		addX = -1;
		break;
	case MoveReceiverDirection::Down:
		addY = -1;
		break;
	case MoveReceiverDirection::Right:
		addX = 1;
		break;
	default:
		break;
	}
	setPosX(x + addX);
	setPosY(y + addY);
}

void Receiver::activate()
{
	this->m_isActive = true;
}

void Receiver::deactivate()
{
	this->m_isActive = false;
}

void Receiver::setPosition(float X, float Y)
{
	setPosX(X);
	setPosY(Y);
}

void Receiver::print() const
{
	std::cout << "Receiver ID: " << m_id << ", x = " << getPosX() << ", y = " << getPosY() << "; isActive: " << m_isActive << "\n";
}

bool Receiver::operator== (Receiver& const otherReceiver) const
{
	bool result = false;
	if (this->getPosX() == otherReceiver.getPosX())
	{
		if (this->getPosY() == otherReceiver.getPosY())
		{
			if (this->ifActive() == otherReceiver.ifActive())
			{
				result = true;
			}
		}
	}
	return result;
}