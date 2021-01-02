#include "Tests.h"

#include <fstream>

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

namespace Tests {

	namespace testPerformance {

		void test0(float* resultStorage)
		{
			populateWithSources(70);
			populateWithObstacles(20);
			listOfReceiversPtr->createReceiver(0, 0);
			listOfReceiversPtr->createReceiver(0, 2);
			listOfReceiversPtr->createReceiver(2, 0);
			listOfReceiversPtr->createReceiver(10, -5);
			listOfReceiversPtr->createReceiver(12, 0);
			listOfReceiversPtr->createReceiver(2, 20);
			listOfReceiversPtr->createReceiver(2, 4);
			listOfReceiversPtr->createReceiver(-2, 10);
			listOfReceiversPtr->activateById(0);
			savingData->saveAll("PerfTest.bin");
			{
				BasicMath::Timer timer(resultStorage);
				updateFunctions->update();
			}
			resultStorage++;
			{
				BasicMath::Timer timer(resultStorage);
				updateFunctions->update();
			}
			resultStorage++;
			{
				BasicMath::Timer timer(resultStorage);
				updateFunctions->update();
			}
			resultStorage++;
			{
				BasicMath::Timer timer(resultStorage);
				updateFunctions->update();
			}
			resultStorage++;
			{
				BasicMath::Timer timer(resultStorage);
				updateFunctions->update();
			}
			resultStorage++;
			{
				BasicMath::Timer timer(resultStorage);
				updateFunctions->update();
			}

			//switch between receivers and remember times
		}

		void test1()
		{
			//delete some sources (like a half?) and see how it will work
		}

		void test2()
		{
			//delete most sources and add new ones (for memory fragmentation), see performance
		}

		void test3()
		{
			//delete most obstacles, add new ones (for memory fragmentation)
		}

		void test4()
		{
			//loading / saving ?
		}

		int testMain()
		{
			PrintErrorLogToFile("-------------------------------------");
			PrintErrorLogToFile("Testing Performance...");
			std::string logFileName = CreateNewPerformanceLogFile("Configuration = Debug");
			
			float resultsStorage[10];
			for (int i = 0; i < 10; i++) { resultsStorage[i] = 0; }
			
			updateFunctions->resetLists();
			test0(resultsStorage);
			PrintToPerformanceLogFile(logFileName, "Test 0:");
			PrintToPerformanceLogFile(logFileName, resultsStorage, 10);
			
			for (int i = 0; i < 10; i++) { resultsStorage[i] = 0; }

			updateFunctions->resetLists();
			test1();
			//PrintToPerformanceLogFile(logFileName, "Test 1:");
			//PrintToPerformanceLogFile(logFileName, resultsStorage, 10);


			PrintErrorLogToFile("End of performance test");


			return 0;
		}

		void populateWithSources(const unsigned int quantity)
		{
			float x = 1;
			float y = 1;
			float Lwa = 100;
			float maxDistance = 150;
			bool isOccludable = true;
			AttenuationType attenType = AttenuationType::PointSource;

			for (int i = 0; i < quantity; i++)
			{
				if (i % 4 == 0)
				{
					x = x < 0 ? (-1) * x : x;
					y = y < 0 ? (-1) * y : y;

					if (i % 5 == 1)
					{
						x = x / 2;
						y = y / 2;
					}
					
					if (x < y)
					{
						x = x + i/4;
					}
					else
					{
						y = y + i/4;
					}
					attenType = attenType == AttenuationType::PointSource ? AttenuationType::LineSource : AttenuationType::PointSource;
				}
				else if (i % 4 == 1)
				{
					y = y * (-1);
				}
				else if (i % 4 == 2)
				{
					x = x * (-1);
				}
				else if (i % 4 == 3)
				{
					y = y * (-1);
				}
				SoundSourceDescriptor sourceDescriptor(x, y, Lwa, maxDistance, isOccludable, attenType);
				listOfSourcesPtr->addSource(sourceDescriptor);
			}
		}

		void populateWithObstacles(const unsigned int quantity)
		{
			float x = 1.5;
			float y = 1.5;
			float x2, y2;
			float damp = 2;
			float maxDistance = 150;
			bool isOccludable = true;
			AttenuationType attenType = AttenuationType::PointSource;

			for (int i = 0; i < quantity; i++)
			{
				if (i % 4 == 0)
				{
					x = x < 0 ? (-1) * x : x;
					y = y < 0 ? (-1) * y : y;

					if (i % 5 == 1)
					{
						x = x / 2;
						y = y / 2;
					}

					if (x < y)
					{
						x = x + i / 4;
					}
					else
					{
						y = y + i / 4;
					}

				}
				else if (i % 4 == 1)
				{
					y = y * (-1);
				}
				else if (i % 4 == 2)
				{
					x = x * (-1);
				}
				else if (i % 4 == 3)
				{
					y = y * (-1);
				}
				x2 = x - 4;
				y2 = y + 4;
				ObstacleDescriptor obstacleDesc(x, y, x2, y2, damp);
				listOfObstaclesPtr->addObstacle(obstacleDesc);
			}
		}

		void populateWithReceivers(const unsigned int quantity)
		{

		}
	}
}