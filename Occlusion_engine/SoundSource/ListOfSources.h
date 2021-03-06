#pragma once
#include "ListOfSourcesInterface.h"
#include "SoundAPI.h"
#include <vector>

class SOUND_API ListOfSources : public ListOfSourcesInterface
{
public:
	SoundSource* addSource(SoundSourceDescriptor &soundSourceDescriptor) override;
	void deleteSourceById(int Id) override;
	void deleteSourceByNr(int Nr) override;
	void deleteAll() override;

	SoundSource* getPtrById(int Id) const override;
	SoundSource* getPtrByNr(int Nr) const override;
	SoundSource* operator[] (int Nr) const override;

	unsigned int getSourcesAmount() const override { return m_sourcesAmount; }
	unsigned int getSourcesAmountLimit() const override { return m_sourcesAmountLimit; }

	ListOfSources();
	~ListOfSources();

private:
	std::vector<SoundSource*> m_listOfPointers;
	int m_nextId = 0;
	unsigned int m_sourcesAmount = 0;
	const unsigned int m_sourcesAmountLimit;

	int getListNrById(int Id) const;
	bool isListIndexValid(int Nr) const;
};

extern SOUND_API ListOfSources* listOfSourcesPtr;