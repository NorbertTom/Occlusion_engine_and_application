#include "SoundEngineInitializer.h"
#include "..\Tests\Tests.h"
#include "ErrorLogging.h"
#include "ListOfObstacles.h"
#include "ListOfReceivers.h"
#include "ListOfSources.h"
#include "LoadingData.h"
#include "NorMemoryPool.h"

namespace SoundEngineInitializer
{
	void initialize()
	{
		LOG_INFO("Application started");
		initializeMemory();		
		Tests::runAllAvailableTests();
		std::cout << "Occlusion program has started. Written by Norbert Tomczak. All rights reserved.\n";
	}

	void initializeMemory()
	{
		// DO NOTHING FOR NOW
	}

	void close()
	{
		delete listOfReceiversPtr;
		delete listOfObstaclesPtr;
		delete listOfSourcesPtr;
		delete loadingData;
		delete norMemoryPool;
		// deal with leaks!
	}
}