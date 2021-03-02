#include "Tests.h"
#include <cstdlib>
#include <vector>

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
	namespace testLoadingAndSaving
	{

		struct TestSoundSource
		{

			float x, y, Lwa, maxDistance, currentAttenuation;
			bool isOccludable, isOccluded, isVirtualized;
			AttenuationType attenuationType;
			//	std::vector<Obstacle*> m_listOfOccluders;

			TestSoundSource(SoundSourceDescriptor& desc) : x(desc.m_x), y(desc.m_y), Lwa(desc.m_Lwa), maxDistance(desc.m_maxDistance),
				isOccludable(desc.m_isOccludable), attenuationType(desc.m_attenuationType) {};
			TestSoundSource() {};
			~TestSoundSource() {};

			TestSoundSource operator= (SoundSource& const source)
			{
				if (&source)
				{
					x = source.getPosX();
					y = source.getPosY();
					Lwa = source.getLwa();
					maxDistance = source.getMaxDistance();
					isOccludable = source.ifOccludable();
					attenuationType = source.getAttenuationType();
					currentAttenuation = source.getCurrentAttenuation();
					isOccluded = source.ifOccluded();
					isVirtualized = source.ifVirtual();
				}
				return *this;
			}

			bool operator== (TestSoundSource& const otherSource) const
			{
				bool result = false;
				if (x == otherSource.x)
				{
					if (y == otherSource.y)
					{
						if (Lwa == otherSource.Lwa)
						{
							if (maxDistance == otherSource.maxDistance)
							{
								if (currentAttenuation == otherSource.currentAttenuation)
								{
									if (attenuationType == otherSource.attenuationType)
									{
										result = true;
									}
								}
							}
						}
					}
				}
				return result;
			}
		};

		struct TestObstacle
		{
			float x1, y1, x2, y2, dampening;

			TestObstacle(ObstacleDescriptor& desc) : x1(desc.m_x1), y1(desc.m_y1), x2(desc.m_x2), y2(desc.m_y2),
				dampening(desc.m_damp) {};
			TestObstacle() {};
			~TestObstacle() {};

			TestObstacle operator= (Obstacle& const obstacle)
			{
				if (&obstacle)
				{
					x1 = obstacle.getPosX1();
					y1 = obstacle.getPosY1();
					x2 = obstacle.getPosX2();
					y2 = obstacle.getPosY2();
					dampening = obstacle.getDampening();
				}
				return *this;
			}

			bool operator== (TestObstacle& const otherObstacle) const
			{
				bool result = false;
				if (x1 == otherObstacle.x1)
				{
					if (x2 == otherObstacle.x2)
					{
						if (y1 == otherObstacle.y1)
						{
							if (y2 == otherObstacle.y2)
							{
								if (dampening == otherObstacle.dampening)
								{
									result = true;
								}
							}
						}
					}
				}
				return result;
			}
		};

		struct TestReceiver
		{
			float x, y;
			bool isActive;

			TestReceiver(float X, float Y, bool IsActive) : x(X), y(Y), isActive(IsActive) {};
			TestReceiver() {};
			~TestReceiver() {};

			TestReceiver operator= (Receiver& const receiver)
			{
				if (&receiver)
				{
					x = receiver.getPosX();
					y = receiver.getPosY();
					isActive = receiver.ifActive();
				}
				return *this;
			}

			bool operator== (TestReceiver& const otherReceiver) const
			{
				bool result = false;
				if (x == otherReceiver.x)
				{
					if (y == otherReceiver.y)
					{
						if (isActive == otherReceiver.isActive)
						{
							result = true;
						}
					}
				}
				return result;
			}
		};

		bool test0(int& failCounter)
		{
			BasicMath::Timer timer;
			bool result = false;
			SoundSourceDescriptor source0Descriptor(1, 2, 100, 92, true, AttenuationType::PointSource);
			SoundSourceDescriptor source1Descriptor(3, 4, 120, 85, false, AttenuationType::LineSource);
			SoundSourceDescriptor source2Descriptor(5, 6, 140, 95, true, AttenuationType::NoAttenuation);
			SoundSource* source[3];
			source[0] = listOfSourcesPtr->addSource(source0Descriptor);
			source[1] = listOfSourcesPtr->addSource(source1Descriptor);
			source[2] = listOfSourcesPtr->addSource(source2Descriptor);
			
			TestSoundSource testSourcePreSave[3];
			for (int i = 0; i < 3; i++)
			{
				testSourcePreSave[i] = *(source[i]);
			}

			ObstacleDescriptor obstacle0Descriptor(1, 2, 3, 4, 10);
			ObstacleDescriptor obstacle1Descriptor(5, 6, 7, 8, 20);
			Obstacle* obstacle[2];
			obstacle[0] = listOfObstaclesPtr->addObstacle(obstacle0Descriptor);
			obstacle[1] = listOfObstaclesPtr->addObstacle(obstacle1Descriptor);

			TestObstacle testObstaclePreSave[2];
			for (int i = 0; i < 2; i++)
			{
				testObstaclePreSave[i] = *(obstacle[i]);
			}

			listOfReceiversPtr->createReceiver(0, 0);
			listOfReceiversPtr->createReceiver(2, -2);
			listOfReceiversPtr->createReceiver(10, 5);
			listOfReceiversPtr->activate(1);

			TestReceiver testReceiverPreSave[3];
			for (int i = 0; i < 3; i++)
			{
				testReceiverPreSave[i] = *(listOfReceiversPtr->getPtrByNr(i));
			}

			updateFunctions->update();
			std::string fileName = "testSave.bin";
			savingData->saveAll(fileName);
			updateFunctions->resetLists();
			loadingData->loadDataFromFile(fileName);
			
			TestSoundSource testSourcePostLoad[3];
			for (int i = 0; i < 3; i++)
			{
				testSourcePostLoad[i] = *(listOfSourcesPtr->getPtrByNr(i));
			}
			TestObstacle testObstaclePostLoad[2];
			for (int i = 0; i < 2; i++)
			{
				testObstaclePostLoad[i] = *(listOfObstaclesPtr->getPtrByNr(i));
			}
			TestReceiver testReceiverPostLoad[3];
			for (int i = 0; i < 3; i++)
			{
				testReceiverPostLoad[i] = *(listOfReceiversPtr->getPtrByNr(i));
			}
			int sourcesEqual = 0;
			int obstaclesEqual = 0;
			int receiversEqual = 0;
			// CHECK IF THEY ARE EQUAL
			for (unsigned int i = 0; i < listOfSourcesPtr->getSourcesAmount(); i++)
			{
				if (testSourcePreSave[i] == testSourcePostLoad[i])
				{
					sourcesEqual++;
				}
			}
			for (unsigned int i = 0; i < listOfObstaclesPtr->getObstaclesAmount(); i++)
			{
				if (testObstaclePreSave[i] == testObstaclePostLoad[i])
				{
					obstaclesEqual++;
				}
			}
			for (unsigned int i = 0; i < listOfReceiversPtr->getReceiversAmount(); i++)
			{
				if (testReceiverPreSave[i] == testReceiverPostLoad[i])
				{
					receiversEqual++;
				}
			}
			if (sourcesEqual == 3 && obstaclesEqual == 2 && receiversEqual == 3)
			{
				result = true;
			}
			else
			{
				PrintErrorLogToFile("test0 failed, sources equal = " + std::to_string(sourcesEqual) + "/3, obstacles equal = "
					+ std::to_string(obstaclesEqual) + "/2,	receivers equal = " + std::to_string(receiversEqual) + "/3");
				failCounter++;
			}
			return result;
		}

		bool test1(int& failCounter)
		{
			BasicMath::Timer timer;
			bool result = ifRandomNrOfObjectsEqual(10, 6, 4, false, true);
			if (!result)
			{
				PrintErrorLogToFile("test1 failed");
				failCounter++;
			}
			return result;
		}

		bool test2(int& failCounter)
		{
			BasicMath::Timer timer;
			bool result = ifRandomNrOfObjectsEqual(31, 19, 11, false, true);
			if (!result)
			{
				PrintErrorLogToFile("test2 failed");
				failCounter++;
			}
			return result;
		}

		bool test3(int& failCounter)
		{
			BasicMath::Timer timer;
			bool result = ifRandomNrOfObjectsEqual(50, 40, 15, true, true);
			if (!result)
			{
				PrintErrorLogToFile("test3 failed");
				failCounter++;
			}
			return result;
		}

		bool test4(int& failCounter)
		{
			BasicMath::Timer timer;
			bool result = ifRandomNrOfObjectsEqual(70, 50, 20, true, false); // do not randomize as it's a test for max capacity
			if (!result)
			{
				PrintErrorLogToFile("test4 failed");
				failCounter++;
			}
			return result;
		}

		int testMain()
		{
			PrintErrorLogToFile("-------------------------------------");
			PrintErrorLogToFile("Testing loading and saving...");

			bool testPassedLoadingSaving[5];
			for (int i = 0; i < sizeof(testPassedLoadingSaving); i++)
				testPassedLoadingSaving[i] = false;
			int failCounter = 0;
			testPassedLoadingSaving[0] = test0(failCounter);
			updateFunctions->resetLists();
			testPassedLoadingSaving[1] = test1(failCounter);
			updateFunctions->resetLists();
			testPassedLoadingSaving[2] = test2(failCounter);
			updateFunctions->resetLists();
			testPassedLoadingSaving[3] = test3(failCounter);
			updateFunctions->resetLists();
			testPassedLoadingSaving[4] = test4(failCounter);
			updateFunctions->resetLists();
			int nrOfTests = sizeof(testPassedLoadingSaving);

			PrintErrorLogToFile("Loading and Saving tests passed: " +
				std::to_string(nrOfTests - failCounter) + "/" + std::to_string(nrOfTests));

			if (failCounter > 0)
				printFailed(testPassedLoadingSaving, sizeof(testPassedLoadingSaving));
			return failCounter;
		}

		bool ifRandomNrOfObjectsEqual(int nrOfSourcesMax, int nrOfObstaclesMax, int nrOfReceiversMax, bool testPostUpdate, bool randomize)
		{
			bool result = false;
			int randomNrOfSources = randomize ? nrOfSourcesMax - rand() % 5 : nrOfSourcesMax;
			std::vector<SoundSource*> source(randomNrOfSources);
			std::vector<TestSoundSource> testSourcePreSave(randomNrOfSources);
			for (int i = 0; i < randomNrOfSources; i++)
			{
				float randX = -10 + static_cast<float>(rand() % 20);
				float randY = -20 + static_cast<float>(rand() % 30);
				float randLwa = 80 + static_cast<float>(rand() % 50);
				float randMaxDistance = 70 + static_cast<float>(rand() % 100);
				bool randIsOccludable = static_cast<bool>(rand() % 1);
				AttenuationType randAttenuationType = static_cast<AttenuationType>(rand() % 3);
				SoundSourceDescriptor sourceDescriptor(randX, randY, randLwa, randMaxDistance, randIsOccludable, randAttenuationType);
				source[i] = listOfSourcesPtr->addSource(sourceDescriptor);
			}
			int randomNrOfObstacles = randomize ? nrOfObstaclesMax - rand() % 3 : nrOfObstaclesMax;
			std::vector<Obstacle*> obstacle(randomNrOfObstacles);
			std::vector<TestObstacle> testObstaclePreSave(randomNrOfObstacles);
			for (int i = 0; i < randomNrOfObstacles; i++)
			{
				float randX1 = -20 + static_cast<float>(rand() % 40);
				float randY1 = -10 + static_cast<float>(rand() % 20);
				float randX2 = -15 + static_cast<float>(rand() % 25);
				float randY2 = -17 + static_cast<float>(rand() % 30);
				float randDampening = 10 + static_cast<float>(rand() % 30);
				ObstacleDescriptor obstacleDescriptor(randX1, randY1, randX2, randY2, randDampening);
				obstacle[i] = listOfObstaclesPtr->addObstacle(obstacleDescriptor);
			}

			int randomNrOfReceivers = randomize ? nrOfReceiversMax - rand() % 4 : nrOfReceiversMax;
			std::vector<Receiver*> receiver(randomNrOfReceivers);
			std::vector<TestReceiver> testReceiverPreSave(randomNrOfReceivers);
			for (int i = 0; i < randomNrOfReceivers; i++)
			{
				float randX = -20 + static_cast<float>(rand() % 40);
				float randY = -20 + static_cast<float>(rand() % 35);
				receiver[i] = listOfReceiversPtr->createReceiver(randX, randY);
			}
			listOfReceiversPtr->activate(rand() % randomNrOfReceivers);
			
			if (testPostUpdate)
			{
				updateFunctions->update();
			}

			for (int i = 0; i < randomNrOfSources; i++)
			{
				testSourcePreSave[i] = *(source[i]);
			}
			for (int i = 0; i < randomNrOfObstacles; i++)
			{
				testObstaclePreSave[i] = *(obstacle[i]);
			}
			for (int i = 0; i < randomNrOfReceivers; i++)
			{
				testReceiverPreSave[i] = *(receiver[i]);
			}

			if (!testPostUpdate)
			{
				updateFunctions->update();
			}

			std::string fileName = "testSave.bin";
			savingData->saveAll(fileName);
			updateFunctions->resetLists();
			loadingData->loadDataFromFile(fileName);
			remove(fileName.c_str());

			if (testPostUpdate)
			{
				updateFunctions->update();
			}

			std::vector<TestSoundSource> testSourcePostLoad(randomNrOfSources);
			for (int i = 0; i < randomNrOfSources; i++)
			{
				testSourcePostLoad[i] = *(listOfSourcesPtr->getPtrByNr(i));
			}
			std::vector<TestObstacle> testObstaclePostLoad(randomNrOfObstacles);
			for (int i = 0; i < randomNrOfObstacles; i++)
			{
				testObstaclePostLoad[i] = *(listOfObstaclesPtr->getPtrByNr(i));
			}
			std::vector<TestReceiver> testReceiverPostLoad(randomNrOfReceivers);
			for (int i = 0; i < randomNrOfReceivers; i++)
			{
				testReceiverPostLoad[i] = *(listOfReceiversPtr->getPtrByNr(i));
			}
			int sourcesEqual = 0;
			int obstaclesEqual = 0;
			int receiversEqual = 0;
			for (int i = 0; i < randomNrOfSources; i++)
			{
				if (testSourcePostLoad[i] == testSourcePreSave[i])
				{
					sourcesEqual++;
				}
			}
			for (int i = 0; i < randomNrOfObstacles; i++)
			{
				if (testObstaclePostLoad[i] == testObstaclePreSave[i])
				{
					obstaclesEqual++;
				}
			}
			for (int i = 0; i < randomNrOfReceivers; i++)
			{
				if (testReceiverPostLoad[i] == testReceiverPreSave[i])
				{
					receiversEqual++;
				}
			}
			if (sourcesEqual == listOfSourcesPtr->getSourcesAmount() && obstaclesEqual == listOfObstaclesPtr->getObstaclesAmount()
				&& receiversEqual == listOfReceiversPtr->getReceiversAmount())
			{
				result = true;
			}
			else
			{
				PrintErrorLogToFile("Sources equal = " + std::to_string(sourcesEqual) + "/" +
					std::to_string(listOfSourcesPtr->getSourcesAmount()) + ", obstacles equal = "
					+ std::to_string(obstaclesEqual) + "/" + std::to_string(listOfObstaclesPtr->getObstaclesAmount()) +
					", receivers equal = " + std::to_string(receiversEqual) + "/" + std::to_string(listOfReceiversPtr->getReceiversAmount()));
			}
			return result;
		}
	}
}