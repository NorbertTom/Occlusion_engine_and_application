#pragma once
#include "SoundAPI.h"
#include "ReceiverInterface.h"
#include "BaseClassesFunctions.h"

class ListOfReceivers;

enum class MoveReceiverDirection {
	Up = 0,
	Left,
	Down,
	Right
};

class SOUND_API Receiver : public BasicMath::Point, public ReceiverInterface
{

public:
	static const int memoryPerObject = 2 * sizeof(float) + sizeof(bool);

	void print() const override;
	void setPosition(float X, float Y) override;
	int getId() const override;
	bool ifActive() const;
	void moveReceiver(MoveReceiverDirection direction);
	bool operator== (Receiver& const otherReceiver) const;

private:
	Receiver(float X, float Y, int Id);
	~Receiver();

	int m_id;
	bool m_isActive;

	void activate() override;
	void deactivate();

	friend class ListOfReceivers;
};