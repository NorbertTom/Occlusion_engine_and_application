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
	namespace testIfSoundSourceListWorks
	{
		bool test0(int& failCounter)
		{
			//If creating new Obstacles works good
			BasicMath::Timer timer;
			const int amount = 10;
			for (int i = 0; i < amount; i++)
			{
				SoundSourceDescriptor sourceDesc(i, i + 2, 100, 100, true, AttenuationType::PointSource);
				listOfSourcesPtr->addSource(sourceDesc);
			}
			int SourcesQuantity = listOfSourcesPtr->getSourcesAmount();
			if (SourcesQuantity == 10)
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
				SoundSourceDescriptor sourceDesc(i, 2*i + 5, 100, 100, true, AttenuationType::PointSource);
				listOfSourcesPtr->addSource(sourceDesc);
			}
			for (int i = 10; i > 0; i--)
			{
				listOfSourcesPtr->deleteSourceByNr(i);
			}
			int SourcesQuantity = listOfSourcesPtr->getSourcesAmount();
			if (SourcesQuantity == 10)
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
				SoundSourceDescriptor sourceDesc(i + 2, i, 85, 100, true, AttenuationType::PointSource);
				listOfSourcesPtr->addSource(sourceDesc);
			}
			for (int i = 10; i > 0; i--)
			{
				listOfSourcesPtr->deleteSourceByNr(i);
			}
			amount = 30;
			for (int i = 0; i < amount; i++)
			{
				SoundSourceDescriptor sourceDesc(i - 2, i+5, 85, 100, true, AttenuationType::PointSource);
				listOfSourcesPtr->addSource(sourceDesc);
			}
			for (int i = 5; i > 0; i--)
			{
				listOfSourcesPtr->deleteSourceByNr(i);
			}
			int SourcesQuantity = listOfSourcesPtr->getSourcesAmount();
			if (SourcesQuantity == 35)
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
			for (int i = 0; i < 60; i++)
			{
				SoundSourceDescriptor sourceDesc(2, 3, 85, 100, true, AttenuationType::PointSource);
				listOfSourcesPtr->addSource(sourceDesc);
			}
			listOfSourcesPtr->deleteAll(); 
			if (listOfSourcesPtr->getSourcesAmount() != 0)
			{
				 failCounter++;
				 return false;
			}
			return true;
		}

		int testMain()
		{
			PrintErrorLogToFile("-------------------------------------");
			PrintErrorLogToFile("Testing if SoundSource list works...");

			bool testPassedSoundSourceList[4];
			for (int i = 0; i < sizeof(testPassedSoundSourceList); i++)
				testPassedSoundSourceList[i] = false;
			int failCounter = 0;
			testPassedSoundSourceList[0] = test0(failCounter);
			updateFunctions->resetLists();
			testPassedSoundSourceList[1] = test1(failCounter);
			updateFunctions->resetLists();
			testPassedSoundSourceList[2] = test2(failCounter);
			updateFunctions->resetLists();
			testPassedSoundSourceList[3] = test3(failCounter);
			updateFunctions->resetLists();
			int nrOfTests = sizeof(testPassedSoundSourceList);

			std::string log = "If SoundSource List Works tests passed: " +
				std::to_string(nrOfTests - failCounter) + "/" + std::to_string(nrOfTests);
			PrintErrorLogToFile(log);

			if (failCounter > 0)
				printFailed(testPassedSoundSourceList, sizeof(testPassedSoundSourceList));
			return failCounter;
		}
	}
}