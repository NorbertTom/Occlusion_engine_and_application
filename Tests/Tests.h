#pragma once

#include <iostream>
#include <string>

namespace Tests {

	enum TestOptions {
		NONE				= 0,
		UnitTests			= 1 << 0,
		PerformanceTests	= 1 << 1,
		SomeFutureTests		= 1 << 2
	};

	inline TestOptions operator+ (TestOptions a, TestOptions b)
	{
		return static_cast<TestOptions>(static_cast<int>(a) | static_cast<int>(b));
	}

	void runTests(TestOptions testOptions);
	void printFailed(bool* testPassed, int size);
	void PrintErrorLogToFile(std::string &&message);
	std::string CreateNewPerformanceLogFile(std::string &&message);
	std::string CreateNewPerformanceLogFile();
	void PrintToPerformanceLogFile(std::string& fileName, const float* firstNumber, const unsigned int quantity);
	void PrintToPerformanceLogFile(std::string& fileName, std::string &&message);

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

	namespace testPerformance
	{
		int testMain();

		void populateWithSources(const unsigned int quantity);
		void populateWithObstacles(const unsigned int quantity);
		void populateWithReceivers(const unsigned int quantity);
		float calculateMean(float* pointerToFirstElement, const unsigned int quantity);
	}
}
