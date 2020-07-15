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
	if (auto receiver = listOfReceiversPtr->getActive())
	{
		soundSourceCalculator->setAllVirtualizations();
		soundSourceCalculator->calculateAllAttenuations();
	}
	else // if no active Receivers exists
	{
		for (int i = 0; i < listOfSourcesPtr->getSourcesAmount(); i++)
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