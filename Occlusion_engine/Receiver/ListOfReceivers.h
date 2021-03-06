#pragma once
#include "ListOfReceiversInterface.h"
#include "SoundAPI.h"
#include <vector>


class SOUND_API ListOfReceivers : public ListOfReceiversInterface
{
public:
	Receiver* createReceiver(float X, float Y) override;
	void deleteReceiverById(int Id) override;
	void deleteReceiverByNr(int Nr) override;
	void deleteAll() override;
	void deleteAllButActive();
	void activate(int nr) const;
	void activateById(int id) const;
	void deactivateAll() const;

	Receiver* getActive() const override;
	Receiver* getPtrById(int Id) const override;
	Receiver* getPtrByNr(int Nr) const override;
	int getListNrById(int Id) const;
	Receiver* operator[](int Nr) const override;

	unsigned int getReceiversAmount() const override { return m_receiversAmount; }
	unsigned int getReceiversAmountLimit() const override {	return m_receiversAmountLimit; }

	ListOfReceivers();
	~ListOfReceivers();

private:
	std::vector<Receiver*> m_listOfPointers;
	int m_nextId = 0;
	unsigned int m_receiversAmount = 0;
	const unsigned int m_receiversAmountLimit;

	bool isListIndexValid(int Nr) const;
};

extern SOUND_API ListOfReceivers* listOfReceiversPtr;