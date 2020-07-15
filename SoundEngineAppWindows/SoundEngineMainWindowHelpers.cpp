#include "SoundEngineMainWindow.h"

#include "SoundAPI.h"
#include "UIDisplayHelper.h"
#include "ListOfReceivers.h"
#include "Receiver.h"
#include "ListOfSources.h"
#include "SoundSource.h"
#include "ListOfObstacles.h"
#include "Obstacle.h"
#include "UpdateFunctions.h"

void SoundEngineMainWindow::resetButtonsState()
{
	buttonSourceEdit->Disable();
	buttonSourceDelete->Disable();
	buttonObstacleEdit->Disable();
	buttonObstacleDelete->Disable();
	buttonReceiverEdit->Disable();
	buttonReceiverDelete->Disable();
}

void SoundEngineMainWindow::refreshWindow()
{
	clearTables();
	updateFunctions->update();
	fillTablesWithObjects();
	resetButtonsState();
}

void SoundEngineMainWindow::fillTablesWithObjects()
{
	int amountOfSources = listOfSourcesPtr->getSourcesAmount();
	for (int i = 0; i < amountOfSources; i++)
	{
		SoundSource* source = listOfSourcesPtr->getPtrByNr(i);
		UIlistOfSources->InsertItem(i, UIDisplayHelper::toString(source->getId()));
		UIlistOfSources->SetItem(i, 1, UIDisplayHelper::toString(source->getPosX()));
		UIlistOfSources->SetItem(i, 2, UIDisplayHelper::toString(source->getPosY()));
		UIlistOfSources->SetItem(i, 3, UIDisplayHelper::toString(source->getCurrentAttenuation()));
		UIlistOfSources->SetItem(i, 4, UIDisplayHelper::toString(source->ifOccluded()));
		UIlistOfSources->SetItem(i, 5, UIDisplayHelper::toString(source->ifVirtual()));
		UIlistOfSources->SetItem(i, 6, UIDisplayHelper::toString(source->getLwa()));
		UIlistOfSources->SetItem(i, 7, UIDisplayHelper::toString(source->getMaxDistance()));
		UIlistOfSources->SetItem(i, 8, UIDisplayHelper::toString(source->ifOccludable()));
		std::string attenuationString = attenuationToString(source->getAttenuationType());
		UIlistOfSources->SetItem(i, 9, attenuationString);
	}
	int amountOfObstacles = listOfObstaclesPtr->getObstaclesAmount();
	for (int i = 0; i < amountOfObstacles; i++)
	{
		Obstacle* obstacle = listOfObstaclesPtr->getPtrByNr(i);
		UIlistOfObstacles->InsertItem(i, UIDisplayHelper::toString(obstacle->getId()));
		UIlistOfObstacles->SetItem(i, 1, UIDisplayHelper::toString(obstacle->getPosX1()));
		UIlistOfObstacles->SetItem(i, 2, UIDisplayHelper::toString(obstacle->getPosY1()));
		UIlistOfObstacles->SetItem(i, 3, UIDisplayHelper::toString(obstacle->getPosX2()));
		UIlistOfObstacles->SetItem(i, 4, UIDisplayHelper::toString(obstacle->getPosY2()));
		UIlistOfObstacles->SetItem(i, 5, UIDisplayHelper::toString(obstacle->getDampening()));
	}
	int amountOfReceivers = listOfReceiversPtr->getReceiversAmount();
	for (int i = 0; i < amountOfReceivers; i++)
	{
		Receiver* receiver = listOfReceiversPtr->getPtrByNr(i);
		UIlistOfReceivers->InsertItem(i, UIDisplayHelper::toString(receiver->getId()));
		UIlistOfReceivers->SetItem(i, 1, UIDisplayHelper::toString(receiver->getPosX()));
		UIlistOfReceivers->SetItem(i, 2, UIDisplayHelper::toString(receiver->getPosY()));
		UIlistOfReceivers->SetItem(i, 3, UIDisplayHelper::toString(receiver->ifActive()));
	}
}

void SoundEngineMainWindow::clearTables()
{
	UIlistOfSources->DeleteAllItems();
	UIlistOfObstacles->DeleteAllItems();
	UIlistOfReceivers->DeleteAllItems();
}

std::string SoundEngineMainWindow::attenuationToString(AttenuationType attenuation)
{
	std::string result;
	if (static_cast<int>(attenuation) == 0)
	{
		result = "PointSource";
	}
	else if (static_cast<int>(attenuation) == 1)
	{
		result = "LineSource";
	}
	else if (static_cast<int>(attenuation) == 2)
	{
		result = "NoAttenuation";
	}
	else
	{
		result = "ERROR";
	}
	return result;
}