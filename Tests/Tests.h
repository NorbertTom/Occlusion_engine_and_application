#pragma once

#include <iostream>
#include <string>

namespace Tests {

	void runAllAvailableTests();
	void printFailed(bool* testPassed, int size);
	void PrintErrorLogToFile(std::string message);

	namespace testIsSoundSourceOccludedByObstacle
	{
		bool test0(int& failCounter), test1(int& failCounter), test2(int& failCounter),
			test3(int& failCounter), test4(int& failCounter), test5(int& failCounter),
			test6(int& failCounter), test7(int& failCounter), test8(int& failCounter),
			test9(int& failCounter);
		
		int testMain();
	}

	namespace testIfObstacleListWorks
	{
		bool test0(int& failCounter), test1(int& failCounter),
			test2(int& failCounter), test3(int& failCounter);

		int testMain();
	}

	namespace testIfSoundSourceListWorks
	{
		bool test0(int& failCounter), test1(int& failCounter),
			test2(int& failCounter), test3(int& failCounter);

		int testMain();
	}

	namespace testSetCurrentAttenuationOnSources
	{
		bool test0(int& failCounter), test1(int& failCounter),
			test2(int& failCounter), test3(int& failCounter),
			test4(int& failCounter);

		int testMain();
	}

	namespace testLoadingAndSaving
	{
		bool test0(int& failCounter), test1(int& failCounter),
			test2(int& failCounter), test3(int& failCounter),
			test4(int& failCounter);

		int testMain();

		bool ifRandomNrOfObjectsEqual(int nrOfSourcesMin, int nrOfObstaclesMin, int nrOfReceiversMin, bool testPostUpdate, bool randomize);


	}
}
