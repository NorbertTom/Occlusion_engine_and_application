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
	namespace testSetCurrentAttenuationOnSources
	{
		bool test0(int& failCounter)
		{
			//Smoketest ;)
			BasicMath::Timer timer;
			
			listOfReceiversPtr->createReceiver(0, 0);
			Receiver* listener = listOfReceiversPtr->getActive();
			
			SoundSourceDescriptor sourceDescriptor[5];
			sourceDescriptor[0].m_x = 0.1f;
			sourceDescriptor[0].m_y = 0.1f;
			listOfSourcesPtr->addSource(sourceDescriptor[0]);
			sourceDescriptor[1].m_x = 0;
			sourceDescriptor[1].m_y = 0.2f;
			listOfSourcesPtr->addSource(sourceDescriptor[1]);
			sourceDescriptor[2].m_x = -0.15f;
			sourceDescriptor[2].m_y = 0;
			listOfSourcesPtr->addSource(sourceDescriptor[2]);
			sourceDescriptor[3].m_x = -0.1f;
			sourceDescriptor[3].m_y = -0.2f;
			listOfSourcesPtr->addSource(sourceDescriptor[3]);
			sourceDescriptor[4].m_x = 0.1f;
			sourceDescriptor[4].m_y = 0;
			listOfSourcesPtr->addSource(sourceDescriptor[4]);
			updateFunctions->update();
			
			for (int i = 0; i < listOfSourcesPtr->getSourcesAmount(); i++)
			{
				if (listOfSourcesPtr->getPtrByNr(i)->getCurrentAttenuation() != 0)
				{
					failCounter++;
					return false;
				}
			}
			return true;
		}

		bool test1(int& failCounter)
		{
			//Checking if Att is correctly assigned to corresponding source
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(0, 0);
			Receiver* listener = listOfReceiversPtr->getActive();
			SoundSourceDescriptor sourceDescriptors[5];
			sourceDescriptors[0].m_x = 3.0f;
			sourceDescriptors[0].m_y = 10.0f;
			sourceDescriptors[1].m_x = 2.0f;
			sourceDescriptors[1].m_y = 7.0f;
			sourceDescriptors[2].m_x = -15.0f;
			sourceDescriptors[2].m_y = 0.0f; 
			sourceDescriptors[3].m_x = 0.1f;
			sourceDescriptors[3].m_y = -0.2f; 
			sourceDescriptors[4].m_x = 10.0f;
			sourceDescriptors[4].m_y = 0.0f; 
			for (int i = 0; i < 5; i++)
			{
				listOfSourcesPtr->addSource(sourceDescriptors[i]);
			}
			updateFunctions->update();
			
			for (int i = 0; i < 3; i++)
			{
				if ( !(listOfSourcesPtr->getPtrByNr(i)) )
				{
					failCounter++;
					return false;
				}
				if (listOfSourcesPtr->getPtrByNr(i)->getCurrentAttenuation() == 0)
				{
					failCounter++;
					return false;
				}
			}
			if ( !(listOfSourcesPtr->getPtrByNr(3)) || !(listOfSourcesPtr->getPtrByNr(4)) )
			{
				failCounter++;
				return false;
			}
			if (listOfSourcesPtr->getPtrByNr(3)->getCurrentAttenuation() != 0)
			{
				failCounter++;
				return false;
			}
			else if (listOfSourcesPtr->getPtrByNr(4) && listOfSourcesPtr->getPtrByNr(2) && (listOfSourcesPtr->getPtrByNr(4)->getCurrentAttenuation() >
				listOfSourcesPtr->getPtrByNr(2)->getCurrentAttenuation()))
			{
				failCounter++;
				return false;
			}
			else
				return true;
		}

		bool test2(int& failCounter)
		{
			//Creating and deleting sources test, very close to listener (att should =0)
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(10, 5);
			Receiver* listener = listOfReceiversPtr->getActive();
			SoundSourceDescriptor sourceDescriptor;
			sourceDescriptor.m_x = 10.1;
			sourceDescriptor.m_y = 5.1;
			for (int i = 0; i < 60; i++)
			{
				listOfSourcesPtr->addSource(sourceDescriptor);
			}
			for (int i = 0; i < 20; i++)
			{
				listOfSourcesPtr->deleteSourceByNr(i);
			}
			sourceDescriptor.m_x = 10;
			sourceDescriptor.m_y = 5.1;
			for (int i = 0; i < 30; i++)
			{
				listOfSourcesPtr->addSource(sourceDescriptor);
			}
			updateFunctions->update();
			for (int i = 0; i < listOfSourcesPtr->getSourcesAmount(); i++)
			{
				if (listOfSourcesPtr->getPtrByNr(i)->getCurrentAttenuation() != 0)
				{
					failCounter++;
					return false;
				}
			}
			return true;
		}

		bool test3(int& failCounter)
		{
			//If each dampening is calculated correctly with each source + receiver weird position
			BasicMath::Timer timer;
			listOfReceiversPtr->createReceiver(1, 1);
			Receiver* listener = listOfReceiversPtr->getActive();
			SoundSourceDescriptor source1Descriptor(1.2f, 1.0f, 90, 90, true, AttenuationType::PointSource);
			SoundSourceDescriptor source2Descriptor(1.0f, 1.2f, 90, 90, true, AttenuationType::PointSource); 
			SoundSourceDescriptor source3Descriptor(0.8f, 0.9f, 90, 90, true, AttenuationType::PointSource); 
			listOfSourcesPtr->addSource(source1Descriptor);
			listOfSourcesPtr->addSource(source2Descriptor);
			listOfSourcesPtr->addSource(source3Descriptor);
			ObstacleDescriptor obstacle1Descriptor(1.1f, 0.8f, 1.1f, 1.2f, 21.0f);
			ObstacleDescriptor obstacle2Descriptor(0.9f, 1.05f, 1.13f, 1.09f, 11.0f);
			ObstacleDescriptor obstacle3Descriptor(0.8f, 1.0f, 0.9f, 0.81f, 7.0f);
			listOfObstaclesPtr->addObstacle(obstacle1Descriptor);
			listOfObstaclesPtr->addObstacle(obstacle2Descriptor); 
			listOfObstaclesPtr->addObstacle(obstacle3Descriptor); 
			updateFunctions->update();
			if (listOfSourcesPtr->getPtrById(0) && listOfSourcesPtr->getPtrById(1) && listOfSourcesPtr->getPtrById(2)
				&& listOfSourcesPtr->getPtrById(0)->getCurrentAttenuation() == listOfObstaclesPtr->getPtrByNr(0)->getDampening()
				&& listOfSourcesPtr->getPtrById(1)->getCurrentAttenuation() == listOfObstaclesPtr->getPtrByNr(1)->getDampening()
				&& listOfSourcesPtr->getPtrById(2)->getCurrentAttenuation() == listOfObstaclesPtr->getPtrByNr(2)->getDampening())
				return true;
			else
			{
				failCounter++;
				return false;
			}
			return true;
		}

		bool test4(int& failCounter)
		{
			//If dampenings do sum up
			BasicMath::Timer timer;
			Receiver* listener = listOfReceiversPtr->createReceiver(10, 10);
			SoundSourceDescriptor source1Desc(40.0f, 10.0f, 90, 100, true, AttenuationType::PointSource);
			SoundSourceDescriptor source2Desc(-20.0f, -5.0f, 90, 100, true, AttenuationType::PointSource);
			listOfSourcesPtr->addSource(source1Desc);
			listOfSourcesPtr->addSource(source2Desc);
			ObstacleDescriptor obstacle1Desc(20.0f, 20.0f, 21.0f, 0.0f, 10.0f);
			ObstacleDescriptor obstacle2Desc(30.0f, 25.0f, 29.0f, 9.0f, 11.0f);
			ObstacleDescriptor obstacle3Desc(-20.0f, 10.0f, 10.0f, -20.0f, 7.0f);
			ObstacleDescriptor obstacle4Desc(-10.0f, 10.0f, 5.0f, -8.0f, 9.0f);
			Obstacle* mur1 = listOfObstaclesPtr->addObstacle(obstacle1Desc);
			Obstacle* mur2 = listOfObstaclesPtr->addObstacle(obstacle2Desc);
			Obstacle* mur3 = listOfObstaclesPtr->addObstacle(obstacle3Desc);
			Obstacle* mur4 = listOfObstaclesPtr->addObstacle(obstacle4Desc);
			updateFunctions->update();
			if (listOfSourcesPtr->getPtrByNr(0)->getCurrentAttenuation() > (mur1->getDampening() + mur2->getDampening())
				&& listOfSourcesPtr->getPtrByNr(1)->getCurrentAttenuation() > (mur3->getDampening() + mur4->getDampening()))
				return true;
			else
			{
				failCounter++;
				return false;
			}
			return true;
		}

		int testMain()
		{
			PrintErrorLogToFile("-------------------------------------");
			PrintErrorLogToFile("Testing SetCurrentAttenuationOnSources method...");
			
			bool testPassedAttenuation[5];
			for (int i = 0; i < sizeof(testPassedAttenuation); i++)
				testPassedAttenuation[i] = false;
			int failCounter = 0;
			testPassedAttenuation[0] = test0(failCounter);
			updateFunctions->resetLists();
			testPassedAttenuation[1] = test1(failCounter);
			updateFunctions->resetLists();
			testPassedAttenuation[2] = test2(failCounter);
			updateFunctions->resetLists();
			testPassedAttenuation[3] = test3(failCounter);
			updateFunctions->resetLists();
			testPassedAttenuation[4] = test4(failCounter);
			updateFunctions->resetLists();
			int nrOfTests = sizeof(testPassedAttenuation);
			
			std::string log = "If Set current attenuation on sources Works tests passed: " +
				std::to_string(nrOfTests - failCounter)	+ "/" + std::to_string(nrOfTests);
			PrintErrorLogToFile(log);

			if (failCounter > 0)
				printFailed(testPassedAttenuation, sizeof(testPassedAttenuation));
			
			return failCounter;
		}
	}
}