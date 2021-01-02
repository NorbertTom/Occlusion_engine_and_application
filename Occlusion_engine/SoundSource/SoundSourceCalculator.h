#pragma once
#include "BaseClassesFunctions.h"

class Obstacle;
class Receiver;
class SoundSource;

class SoundSourceCalculator
{
public:
	void setAllVirtualizations(Receiver* activeReceiverPtr);
	void clearAllListsOfOccluders();
	void calculateAllAttenuations(Receiver* activeReceiverPtr);

private:
	bool IsOccludedByObstacle(SoundSource* sourcePtr, Obstacle const * obstacPtr, Receiver* activeReceiverPtr) const;
	float calculateOcclusion(SoundSource* source, Receiver* activeReceiverPtr) const;
	float distanceAttenuation(SoundSource* sourcePtr, Receiver* activeReceiverPtr) const;
	BasicMath::Line raycast(SoundSource* sourcePtr, Receiver* activeReceiverPtr) const;
	bool shouldBeVirtual(SoundSource* source, Receiver* receiver) const;

};

extern SoundSourceCalculator* soundSourceCalculator;