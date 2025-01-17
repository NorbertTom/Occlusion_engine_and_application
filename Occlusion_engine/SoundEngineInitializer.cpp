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
		Tests::runTests(Tests::TestOptions::UnitTests + Tests::TestOptions::PerformanceTests);
		std::cout << "Occlusion program has started. Written by Norbert Tomczak. All rights reserved.\n";
	}

	void initializeMemory()
	{
		// DO NOTHING FOR NOW
	}

	void close()
	{
		LOG_INFO("Application closing");
		delete listOfReceiversPtr;
		delete listOfObstaclesPtr;
		delete listOfSourcesPtr;
		delete loadingData;
		delete norMemoryPool;
	}
}