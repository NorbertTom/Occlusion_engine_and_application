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
	namespace testIfObstacleListWorks
	{
		bool test0(int& failCounter)
		{
			//If creating new Obstacles works good
			BasicMath::Timer timer;
			const int amount = 10;
			for (int i = 0; i < amount; i++)
			{
				ObstacleDescriptor obstacleDescriptor(i, i + 2, i + 1, i + 3, i+10);
				listOfObstaclesPtr->addObstacle(obstacleDescriptor);
			}
			int ObstacleQuantity = listOfObstaclesPtr->getObstaclesAmount();
			if (ObstacleQuantity == 10)
				return true;
			else
			{
				failCounter++;
				return false;
			}
			return true;
		}

		bool test1(int& failCounter)
		{
			//If deleting works good
			BasicMath::Timer timer;
			const int amount = 20;
			for (int i = 0; i < amount; i++)
			{
				ObstacleDescriptor obstacleDescriptor(i, i + 2, i + 1, i + 3, i + 10);
				listOfObstaclesPtr->addObstacle(obstacleDescriptor);
			}
			for (int i = 10; i > 0; i--)
			{
				listOfObstaclesPtr->deleteObstacleByNr(i);
			}
			int ObstacleQuantity = listOfObstaclesPtr->getObstaclesAmount();
			if (ObstacleQuantity == 10)
				return true;
			else
			{
				failCounter++;
				return false;
			}
			return true;
		}

		bool test2(int& failCounter)
		{
			//If deleting and creating works good
			BasicMath::Timer timer;
			int amount = 20;
			for (int i = 0; i < amount; i++)
			{
				ObstacleDescriptor obstacleDescriptor(i, i + 2, i + 1, i + 3, i + 10);
				listOfObstaclesPtr->addObstacle(obstacleDescriptor);
			}
			for (int i = 10; i > 0; i--)
			{
				listOfObstaclesPtr->deleteObstacleByNr(i);
			}
			amount = 30;
			for (int i = 0; i < amount; i++)
			{
				ObstacleDescriptor obstacleDescriptor(i, i + 2, i + 1, i + 3, i + 10);
				listOfObstaclesPtr->addObstacle(obstacleDescriptor);
			}
			for (int i = 5; i > 0; i--)
			{
				listOfObstaclesPtr->deleteObstacleByNr(i);
			}
			int ObstacleQuantity = listOfObstaclesPtr->getObstaclesAmount();
			if (ObstacleQuantity == 35)
				return true;
			else
			{
				failCounter++;
				return false;
			}

		}

		bool test3(int& failCounter)
		{
			//If DeleteAll works
			BasicMath::Timer timer;
			ObstacleDescriptor obstacleDesc(1, 2, 3, 4, 5);
			for (int i = 0; i < 50; i++)
			{
				listOfObstaclesPtr->addObstacle(obstacleDesc);
			}
			listOfObstaclesPtr->deleteAll();
			if (listOfObstaclesPtr->getObstaclesAmount() != 0)
				{
					failCounter++;
					return false;
				}
			return true;
		}

		int testMain()
		{
			PrintErrorLogToFile("-------------------------------------");
			PrintErrorLogToFile("Testing if Obstacle list works...");
			
			bool testPassedObstacleList[4];
			for (int i = 0; i < sizeof(testPassedObstacleList); i++)
				testPassedObstacleList[i] = false;
			int failCounter = 0;
			testPassedObstacleList[0] = test0(failCounter);
			updateFunctions->resetLists();
			testPassedObstacleList[1] = test1(failCounter);
			updateFunctions->resetLists();
			testPassedObstacleList[2] = test2(failCounter);
			updateFunctions->resetLists();
			testPassedObstacleList[3] = test3(failCounter);
			updateFunctions->resetLists();
			int nrOfTests = sizeof(testPassedObstacleList);
			
			PrintErrorLogToFile("If Obstacle List Works tests passed: " +
				std::to_string(nrOfTests - failCounter) + "/" + std::to_string(nrOfTests));

			if (failCounter > 0)
				printFailed(testPassedObstacleList, sizeof(testPassedObstacleList));
		
			return failCounter;
		}
	}
}