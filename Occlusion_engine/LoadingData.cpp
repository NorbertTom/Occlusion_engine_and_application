#include "LoadingData.h"

#include <string>

#include "BaseClassesFunctions.h"
#include "Obstacle.h"
#include "SoundSource.h"
#include "Receiver.h"
#include "ListOfSources.h"
#include "ListOfObstacles.h"
#include "ListOfReceivers.h"
#include "FileUtils.h"
#include "ErrorLogging.h"
#include "SavingData.h"
#include "UpdateFunctions.h"

LoadingData* loadingData = new LoadingData();

namespace 
{
	const int sizeOfInt = sizeof(int);
	const int sizeOfFloat = sizeof(float);
	const int sizeOfBool = sizeof(bool);
	const int sizeOfAttenuationType = sizeof(AttenuationType);
}

LoadingData::LoadingData()
{
}

LoadingData::~LoadingData()
{
}

bool LoadingData::loadDataFromFile(std::string& fileName)
{
	LOG_INFO("Loading data from file");
	bool isLoadingSuccesfull = false;
	FileUtils::addExtensionToFilename(fileName);
	std::ifstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	if (file.is_open())
	{
		updateFunctions->resetLists();
		loadSourcesSuccess = loadSources(file);
		loadObstaclesSuccess = loadObstacles(file);
		loadReceiversSuccess = loadReceivers(file);
		file.close();
		isLoadingSuccesfull = true;
	}
	else
	{
		std::cout << "Wrong filename\n";
		LOG_WARNING("Wrong filename during loading: " + fileName);
	}
	return isLoadingSuccesfull;
}

bool LoadingData::loadSources(std::ifstream& file)
{
	bool ifSuccess = false;
	char buffer1[sizeOfInt];
	file.read(buffer1, sizeOfInt);
	int* numberOfObjects = reinterpret_cast<int*>(buffer1);
		for (int i = 0; i < *numberOfObjects; i++)
		{
			char buffer2[SoundSource::memoryPerObject];
			file.read(buffer2, SoundSource::memoryPerObject);
			char* movingBuffer = &(buffer2[0]);
			float x, y, Lwa, maxDistance;
			bool isOccludable;
			AttenuationType attenuation;

			memcpy(&x, movingBuffer, sizeOfFloat);
			movingBuffer = movingBuffer + sizeOfFloat;

			memcpy(&y, movingBuffer, sizeOfFloat);
			movingBuffer = movingBuffer + sizeOfFloat;

			memcpy(&Lwa, movingBuffer, sizeOfFloat);
			movingBuffer = movingBuffer + sizeOfFloat;

			memcpy(&attenuation, movingBuffer, sizeOfAttenuationType);
			movingBuffer = movingBuffer + sizeOfAttenuationType;

			memcpy(&maxDistance, movingBuffer, sizeOfFloat);
			movingBuffer = movingBuffer + sizeOfFloat;

			memcpy(&isOccludable, movingBuffer, sizeOfBool);

			SoundSourceDescriptor newSourceDescriptor(x, y, Lwa, maxDistance, isOccludable, attenuation);
			listOfSourcesPtr->addSource(newSourceDescriptor);
		}
		ifSuccess = true;
		LOG_INFO("Sources loaded succesfully");
		return ifSuccess;
}

bool LoadingData::loadObstacles(std::ifstream& file)
{
	bool ifSuccess = false;
	char buffer1[sizeOfInt];
	file.read(buffer1, sizeOfInt);
	int* numberOfObjects = reinterpret_cast<int*>(buffer1);
		for (int i = 0; i < *numberOfObjects; i++)
		{
			char buffer2[Obstacle::memoryPerObject];
			file.read(buffer2, Obstacle::memoryPerObject);
			char* movingBuffer = &(buffer2[0]);
			float x1, y1, x2, y2, damp;

			memcpy(&x1, movingBuffer, sizeOfFloat);
			movingBuffer = movingBuffer + sizeOfFloat;

			memcpy(&y1, movingBuffer, sizeOfFloat);
			movingBuffer = movingBuffer + sizeOfFloat;

			memcpy(&x2, movingBuffer, sizeOfFloat);
			movingBuffer = movingBuffer + sizeOfFloat;

			memcpy(&y2, movingBuffer, sizeOfFloat);
			movingBuffer = movingBuffer + sizeOfFloat;

			memcpy(&damp, movingBuffer, sizeOfFloat);

			ObstacleDescriptor newObstacleDescriptor(x1, y1, x2, y2, damp);
			listOfObstaclesPtr->addObstacle(newObstacleDescriptor);
		}
		ifSuccess = true;
		LOG_INFO("Obstacles loaded succesfully"); 
		return ifSuccess;
}

bool LoadingData::loadReceivers(std::ifstream& file)
{
	bool ifSuccess = false;
	char buffer1[sizeOfInt];
	file.read(buffer1, sizeOfInt);
	int* numberOfObjects = reinterpret_cast<int*>(buffer1);
	int whichActive = 0;

	for (int i = 0; i < *numberOfObjects; i++)
	{
		char buffer2[Receiver::memoryPerObject];
		file.read(buffer2, Receiver::memoryPerObject);
		char* movingBuffer = &(buffer2[0]);

		float x, y;
		bool isActive;

		memcpy(&x, movingBuffer, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;

		memcpy(&y, movingBuffer, sizeOfFloat);
		movingBuffer = movingBuffer + sizeOfFloat;

		memcpy(&isActive, movingBuffer, sizeOfBool);

		if (isActive == true)
		{
			whichActive = i;
		}

		listOfReceiversPtr->createReceiver(x, y);
	}
	listOfReceiversPtr->activate(whichActive);
	ifSuccess = true;
	LOG_INFO("Receivers loaded succesfully");
	return ifSuccess;
}

bool LoadingData::wasLoadingSuccessfull()
{
	bool result = false;
	if (loadObstaclesSuccess == true && loadObstaclesSuccess == true && loadReceiversSuccess == true)
	{
		result = true;
	}
	loadingSuccess = result;
	return result;
}