#include "UpdateFunctions.h"
#include "SoundSourceCalculator.h"
#include "ListOfSources.h"
#include "ListOfObstacles.h"
#include "ListOfReceivers.h"
#include "SoundSource.h"

UpdateFunctions* updateFunctions; 

UpdateFunctions::UpdateFunctions()
{
}

UpdateFunctions::~UpdateFunctions()
{
}

void UpdateFunctions::update()
{
	soundSourceCalculator->clearAllListsOfOccluders();
	if (Receiver* activeReceiverPtr = listOfReceiversPtr->getActive())
	{
		soundSourceCalculator->setAllVirtualizations(activeReceiverPtr);
		soundSourceCalculator->calculateAllAttenuations(activeReceiverPtr);
	}
	else // if no active Receivers exists
	{
		for (unsigned int i = 0; i < listOfSourcesPtr->getSourcesAmount(); i++)
		{
			SoundSource* source = listOfSourcesPtr->getPtrByNr(i);
			source->setIsVirtualized(true);
			source->setAttenuation(0);
		}
	}
}

void UpdateFunctions::resetLists()
{
	listOfSourcesPtr->deleteAll();
	listOfObstaclesPtr->deleteAll();
	listOfReceiversPtr->deleteAll();
}