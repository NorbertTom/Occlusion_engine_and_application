#pragma once

class Receiver;

class ReceiverInterface
{
public:
	virtual void setPosition(float X, float Y) = 0;
	virtual void activate() = 0;
	virtual void print() const = 0;
	virtual int getId() const = 0;
};