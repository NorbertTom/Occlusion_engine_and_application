#include "Tests.h"

#include "BaseClassesFunctions.h"
#include "Obstacle.h"
#include "SoundSource.h"
#include "Receiver.h"
#include "ListOfSources.h"
#include "ListOfObstacles.h"
#include "ListOfReceivers.h"
#include "UpdateFunctions.h"
#include "LoadingData.h"
#include "SavingData.h"

namespace Tests
{
	namespace testIsSoundSourceOccludedByObstacle
	{
		bool test0(int& failCounter)
		{
			BasicMath::Timer timer;
			
			Receiver* listener = listOfReceiversPtr->createReceiver(0, 0);
			SoundSourceDescriptor source1Desc(5.0f, 10.0f, 100, 100, true, AttenuationType::PointSource);
			SoundSource* source1 = listOfSourcesPtr->addSource(source1Desc);
			ObstacleDescriptor obstacleDesc(0, 2, 4, 3, 10);
			listOfObstaclesPtr->addObstacle(obstacleDesc);
			updateFunctions->update();
			if (!source1->ifOccluded())
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		bool test1(int& failCounter)
		{
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(5, 1);
			SoundSourceDescriptor sourceDesc(10.0f, 20.0f, 100, 100, true, AttenuationType::PointSource);
			SoundSource* source1 = listOfSourcesPtr->addSource(sourceDesc);
			ObstacleDescriptor obstacleDesc(0, 2, 4, 3, 10);
			listOfObstaclesPtr->addObstacle(obstacleDesc);
			updateFunctions->update();
			if (source1->ifOccluded())
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		bool test2(int& failCounter)
		{
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(1, 1);
			SoundSourceDescriptor sourceDesc(5.0f, 10.0f, 100.0f, 100.0f, true, AttenuationType::PointSource);
			SoundSource* source1 = listOfSourcesPtr->addSource(sourceDesc);
			ObstacleDescriptor obstacleDesc(0, 2, 4, 3, 10);
			listOfObstaclesPtr->addObstacle(obstacleDesc);
			updateFunctions->update();
			if (!source1->ifOccluded())
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		bool test3(int& failCounter)
		{
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(1, 1);
			SoundSourceDescriptor sourceDesc(2.0f, 1.0f, 100.0f, 100.0f, true, AttenuationType::PointSource);
			SoundSource* source1 = listOfSourcesPtr->addSource(sourceDesc);
			ObstacleDescriptor obstacleDesc(0, 2, 4, 3, 10);
			listOfObstaclesPtr->addObstacle(obstacleDesc);
			updateFunctions->update();
			if (source1->ifOccluded())
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		bool test4(int& failCounter)
		{
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(1, 1);
			SoundSourceDescriptor sourceDesc(1.0f, 4.0f, 100.0f, 100.0f, true, AttenuationType::PointSource);
			SoundSource* source1 = listOfSourcesPtr->addSource(sourceDesc);
			ObstacleDescriptor obstacleDesc(0, 2, 4, 3, 10);
			listOfObstaclesPtr->addObstacle(obstacleDesc);
			updateFunctions->update();
			if (!source1->ifOccluded())
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		bool test5(int& failCounter)
		{
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(1, 1);
			SoundSourceDescriptor sourceDesc(3.0f, 4.0f, 100.0f, 100.0f, true, AttenuationType::PointSource);
			SoundSource* source1 = listOfSourcesPtr->addSource(sourceDesc);
			ObstacleDescriptor obstacleDesc(2, 0, 2, 5, 10);
			listOfObstaclesPtr->addObstacle(obstacleDesc);
			updateFunctions->update();
			if (!source1->ifOccluded())
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		bool test6(int& failCounter)
		{
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(0, 0);
			SoundSourceDescriptor sourceDesc(0.0f, 5.0f, 100.0f, 100.0f, true, AttenuationType::PointSource);
			SoundSource* source1 = listOfSourcesPtr->addSource(sourceDesc);
			ObstacleDescriptor obstacleDesc(0, 0, 0, 3, 10);
			listOfObstaclesPtr->addObstacle(obstacleDesc);
			updateFunctions->update();
			if (!source1->ifOccluded())
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		bool test7(int& failCounter)
		{
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(2, 2);
			SoundSourceDescriptor sourceDesc(2.0f, 7.0f, 100.0f, 100.0f, true, AttenuationType::PointSource);
			SoundSource* source1 = listOfSourcesPtr->addSource(sourceDesc);
			ObstacleDescriptor obstacleDesc(2, 0, 2, 1, 10);
			listOfObstaclesPtr->addObstacle(obstacleDesc);
			updateFunctions->update();
			if (source1->ifOccluded())
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		bool test8(int& failCounter)
		{
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(-5, 2);
			SoundSourceDescriptor sourceDesc(2.0f, 7.0f, 100.0f, 100.0f, true, AttenuationType::PointSource);
			SoundSource* source1 = listOfSourcesPtr->addSource(sourceDesc);
			ObstacleDescriptor obstacleDesc(0, 5, 0, 6, 10);
			listOfObstaclesPtr->addObstacle(obstacleDesc);
			updateFunctions->update();
			if (!source1->ifOccluded())
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		bool test9(int& failCounter)
		{
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(-10, -9);
			SoundSourceDescriptor sourceDesc(-14.0f, -20.0f, 100.0f, 100.0f, true, AttenuationType::PointSource);
			SoundSource* source1 = listOfSourcesPtr->addSource(sourceDesc);
			ObstacleDescriptor obstacleDesc(-20, -5, -10, -8, 10);
			listOfObstaclesPtr->addObstacle(obstacleDesc);
			updateFunctions->update();
			if (source1->ifOccluded())
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		int testMain()
		{
			PrintErrorLogToFile("-------------------------------------");
			PrintErrorLogToFile("Testing if occlusion works...");
			
			bool testIsSoundSourceOccludedByObstacleResult[10];
			for (int i = 0; i < sizeof(testIsSoundSourceOccludedByObstacleResult); i++)
				testIsSoundSourceOccludedByObstacleResult[i] = false;

			int failCounter = 0;
			testIsSoundSourceOccludedByObstacleResult[0] = test0(failCounter);
			updateFunctions->resetLists();
			testIsSoundSourceOccludedByObstacleResult[1] = test1(failCounter);
			updateFunctions->resetLists();
			testIsSoundSourceOccludedByObstacleResult[2] = test2(failCounter);
			updateFunctions->resetLists();
			testIsSoundSourceOccludedByObstacleResult[3] = test3(failCounter);
			updateFunctions->resetLists();
			testIsSoundSourceOccludedByObstacleResult[4] = test4(failCounter);
			updateFunctions->resetLists();
			testIsSoundSourceOccludedByObstacleResult[5] = test5(failCounter);
			updateFunctions->resetLists();
			testIsSoundSourceOccludedByObstacleResult[6] = test6(failCounter);
			updateFunctions->resetLists();
			testIsSoundSourceOccludedByObstacleResult[7] = test7(failCounter);
			updateFunctions->resetLists();
			testIsSoundSourceOccludedByObstacleResult[8] = test8(failCounter);
			updateFunctions->resetLists();
			testIsSoundSourceOccludedByObstacleResult[9] = test9(failCounter);
			updateFunctions->resetLists();
			int nrOfTests = sizeof(testIsSoundSourceOccludedByObstacleResult);

			PrintErrorLogToFile("Is Sound Source Occluded By Obstacle Tests passed: " +
				std::to_string(nrOfTests - failCounter) + "/" + std::to_string(nrOfTests));

			if (failCounter > 0)
			{
				printFailed(testIsSoundSourceOccludedByObstacleResult, sizeof(testIsSoundSourceOccludedByObstacleResult));
			}
			return failCounter;
		}
	}
}
