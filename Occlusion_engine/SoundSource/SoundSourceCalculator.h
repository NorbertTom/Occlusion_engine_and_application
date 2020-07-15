#pragma once
#include "BaseClassesFunctions.h"

class Obstacle;
class Receiver;
class SoundSource;

class SoundSourceCalculator
{
public:
	void setAllVirtualizations();
	void clearAllListsOfOccluders();
	void calculateAllAttenuations();

private:
	bool IsOccludedByObstacle(SoundSource* sourcePtr, Obstacle const * obstacPtr) const;
	float calculateOcclusion(SoundSource* source) const;
	float distanceAttenuation(SoundSource* sourcePtr, Receiver* activeReceiverPtr) const;
	BasicMath::Line raycast(SoundSource* sourcePtr) const;
	bool shouldBeVirtual(SoundSource* source, Receiver* receiver) const;

};

extern SoundSourceCalculator* soundSourceCalculator;