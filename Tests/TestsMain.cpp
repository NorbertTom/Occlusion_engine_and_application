#include "Tests.h"

#include <string>

#include "ErrorLogging.h"


namespace Tests {

	void runAllAvailableTests()
	{
		LOG_INFO("\n--------------------------------\nTesting started");
		PrintErrorLogToFile("Testing started!");
		int nrOfFailures = 0;
		nrOfFailures = nrOfFailures + testIsSoundSourceOccludedByObstacle::testMain();
		nrOfFailures = nrOfFailures + testIfObstacleListWorks::testMain();
		nrOfFailures = nrOfFailures + testIfSoundSourceListWorks::testMain();
		nrOfFailures = nrOfFailures + testSetCurrentAttenuationOnSources::testMain();
		nrOfFailures = nrOfFailures + testLoadingAndSaving::testMain();

		if (nrOfFailures > 0)
		{
			std::cout << "Some tests failed, please see the log file !TestsLog.txt\n\n";
			PrintErrorLogToFile("\nMind the errors!");
			LOG_WARNING("Mind the errors in tests!");
		}
		else
		{
			PrintErrorLogToFile("\nNo errors in tests");
			LOG_INFO("No errors in tests");
		}
		LOG_INFO("\nEnd of testing\n--------------------------------");
		PrintErrorLogToFile("End of testing!");
	}

	void printFailed(bool* testPassed, int size)
	{
		for (int i = 0; i < size; i++)
		{
			if (!*(testPassed + i))
			{
				std::string log = "ERROR: Test " + std::to_string(i) + " not passed";
				PrintErrorLogToFile(log);
			}
		}
	}
}