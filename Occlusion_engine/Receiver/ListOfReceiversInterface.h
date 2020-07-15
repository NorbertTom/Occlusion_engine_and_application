#pragma once

class Receiver;

class ListOfReceiversInterface
{
public:
	virtual Receiver* createReceiver(float X, float Y) = 0;
	virtual void deleteReceiverById(int Id) = 0;
	virtual void deleteReceiverByNr(int Nr) = 0;
	virtual void deleteAll() = 0;

	virtual Receiver* getActive() const = 0;
	virtual Receiver* getPtrById(int Id) const = 0;
	virtual Receiver* getPtrByNr(int Nr) const = 0;
	virtual Receiver* operator[](int Nr) const = 0;

	virtual int getReceiversAmount() const = 0;

};