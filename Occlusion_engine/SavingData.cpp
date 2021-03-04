#include "SavingData.h"

#include "SoundSource.h"
#include "Obstacle.h"
#include "Receiver.h"
#include "ListOfSources.h"
#include "ListOfObstacles.h"
#include "ListOfReceivers.h"
#include "FileUtils.h"
#include "ErrorLogging.h"

SavingData* savingData;

namespace {
	const int sizeOfInt = sizeof(int);
	const int sizeOfFloat = sizeof(float);
	const int sizeOfBool = sizeof(bool);
	const int sizeOfAttenuationType = sizeof(AttenuationType);
}

SavingData::SavingData()
{
}

SavingData::~SavingData()
{
}


void SavingData::saveAll(std::string fileName)
{
	saveAllToBinFile(fileName);
}

bool SavingData::saveAllToBinFile(std::string& fileName)
{
	FileUtils::addExtensionToFilename(fileName);
	bool allWell = false;
	bool saveSuccess[3];
	for (int i = 0; i < 3; i++)
	{
		saveSuccess[i] = false;
	}
	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);
	
	if (file.is_open())
	{
		saveSuccess[0] = saveSources(file);
		saveSuccess[1] = saveObstacles(file);
		saveSuccess[2] = saveReceivers(file);
		file.close();
	}
	if (saveSuccess[0] == true && saveSuccess[1] == true && saveSuccess[2] == true)
	{
		LOG_INFO("Saved succesfully!");
		allWell = true;
	}
	else
	{
		LOG_ERROR("Error during saving file!");
	}
	return allWell;
}

bool SavingData::saveSources(std::ofstream& file)
{
	bool success = false;
	int numberOfObjects = listOfSourcesPtr->getSourcesAmount();
	file.write(reinterpret_cast<char*>(&numberOfObjects), sizeOfInt);
	for (int i = 0; i < numberOfObjects; i++)
	{
		char buffer[SoundSource::memoryPerObject];
		char* movingBuffer = &buffer[0];
		SoundSource* objectPtr = listOfSourcesPtr->getPtrByNr(i);
		float x = objectPtr->getPosX();
		float y = objectPtr->getPosY();
		float Lwa = objectPtr->getLwa();
		AttenuationType attenuation = objectPtr->getAttenuationType();
		float maxDistance = objectPtr->getMaxDistance();
		bool isOccludable = objectPtr->ifOccludable();

		memcpy(movingBuffer, &x, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;
		
		memcpy(movingBuffer, &y, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;
		
		memcpy(movingBuffer, &Lwa, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;
		
		memcpy(movingBuffer, &attenuation, sizeOfAttenuationType);
		movingBuffer = movingBuffer + sizeOfAttenuationType;
		
		memcpy(movingBuffer, &maxDistance, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;
		
		memcpy(movingBuffer, &isOccludable, sizeOfBool);
		file.write(buffer, SoundSource::memoryPerObject);
	}
	success = true;
	return success;
}

bool SavingData::saveObstacles(std::ofstream& file)
{
	bool success = false;
	int numberOfObjects = listOfObstaclesPtr->getObstaclesAmount();
	file.write(reinterpret_cast<char*>(&numberOfObjects), sizeOfInt);
	for (int i = 0; i < numberOfObjects; i++)
	{
		char buffer[Obstacle::memoryPerObject];
		char* movingBuffer = &buffer[0];
		Obstacle* objectPtr = listOfObstaclesPtr->getPtrByNr(i);
		float x1 = objectPtr->getPosX1();
		float y1 = objectPtr->getPosY1();
		float x2 = objectPtr->getPosX2();
		float y2 = objectPtr->getPosY2();
		float dampening = objectPtr->getDampening();

		memcpy(movingBuffer, &x1, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;

		memcpy(movingBuffer, &y1, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;

		memcpy(movingBuffer, &x2, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;

		memcpy(movingBuffer, &y2, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;

		memcpy(movingBuffer, &dampening, sizeOfFloat);

		file.write(buffer, Obstacle::memoryPerObject);
	}
	success = true;
	return success;
}

bool SavingData::saveReceivers(std::ofstream& file)
{
	bool success = false;
	int numberOfObjects = listOfReceiversPtr->getReceiversAmount();
	file.write(reinterpret_cast<char*>(&numberOfObjects), sizeOfInt);
	for (int i = 0; i < numberOfObjects; i++)
	{
		char buffer[Receiver::memoryPerObject];
		char* movingBuffer = &buffer[0];
		Receiver* objectPtr = listOfReceiversPtr->getPtrByNr(i);
		float x = objectPtr->getPosX();
		float y = objectPtr->getPosY();
		bool isActive = objectPtr->ifActive();

		memcpy(movingBuffer, &x, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;

		memcpy(movingBuffer, &y, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;

		memcpy(movingBuffer, &isActive, sizeOfBool);
		file.write(buffer, Receiver::memoryPerObject);
	}
	success = true;
	return success;
}