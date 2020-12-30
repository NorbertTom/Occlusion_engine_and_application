#include "Tests.h"

#include <string>

#include "ErrorLogging.h"


namespace Tests {

	void runTests(TestOptions testOptions)
	{
		LOG_INFO("\n--------------------------------\nTesting started");
		PrintErrorLogToFile("Testing started!");
		int nrOfFailures = 0;

		if (testOptions & TestOptions::UnitTests)
		{
			PrintErrorLogToFile("\nPerforming Unit Tests");
			nrOfFailures = nrOfFailures + testIsSoundSourceOccludedByObstacle::testMain();
			nrOfFailures = nrOfFailures + testIfObstacleListWorks::testMain();
			nrOfFailures = nrOfFailures + testIfSoundSourceListWorks::testMain();
			nrOfFailures = nrOfFailures + testSetCurrentAttenuationOnSources::testMain();
			nrOfFailures = nrOfFailures + testLoadingAndSaving::testMain();
		}
		if (testOptions & TestOptions::PerformanceTests)
		{
			PrintErrorLogToFile("\nPerforming Performance Tests");
			testPerformance::testMain();
		}
		if (testOptions & TestOptions::SomeFutureTests)
		{
			PrintErrorLogToFile("\nPerforming SomeFuture Tests");
		}
		if (testOptions == TestOptions::NONE)
		{
			PrintErrorLogToFile("\nNo tests performed");
		}

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
				PrintErrorLogToFile("ERROR: Test " + std::to_string(i) + " not passed");
			}
		}
	}
}