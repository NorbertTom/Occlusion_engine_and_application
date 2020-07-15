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

	int getSourcesAmount() const override { return m_sourcesAmount; }
	ListOfSources();
	~ListOfSources();

private:
	std::vector<SoundSource*> m_listOfPointers;
	int m_nextId = 0;
	int m_sourcesAmount = 0;

	int getListNrById(int Id) const;
};

extern SOUND_API ListOfSources* listOfSourcesPtr;
//extern NorMemoryPoolChunk* sourcesMemoryPool;