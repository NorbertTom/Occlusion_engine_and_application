#pragma once

class SoundSource;
struct SoundSourceDescriptor;


class ListOfSourcesInterface
{
public:
	virtual SoundSource* addSource(SoundSourceDescriptor &soundSourceDescriptor) = 0;
	virtual void deleteSourceById(int Id) = 0;
	virtual void deleteSourceByNr(int Nr) = 0;
	virtual void deleteAll() = 0;

	virtual SoundSource* getPtrById(int Id) const = 0;
	virtual SoundSource* getPtrByNr(int Nr) const = 0;
	virtual SoundSource* operator[] (int Nr) const = 0;

	virtual unsigned int getSourcesAmount() const = 0;
	virtual unsigned int getSourcesAmountLimit() const = 0;
};