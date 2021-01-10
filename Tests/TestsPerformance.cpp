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
			populateWithReceivers(20);
			//savingData->saveAll("PerfTest.bin");

			for (int i = 0; i < 10; i++)
			{
				listOfReceiversPtr->activate(2*i);
				BasicMath::Timer timer(resultStorage + i);
				updateFunctions->update();
			}
		}

		void test1(float* resultStorage)
		{
			populateWithSources(70);
			populateWithObstacles(20);
			populateWithReceivers(20);
			
			for (int i = 0; i < 20; i++)
			{
				listOfSourcesPtr->deleteSourceByNr(2 * i);
			}

			for (int i = 0; i < 10; i++)
			{
				listOfReceiversPtr->activate(2 * i);
				BasicMath::Timer timer(resultStorage + i);
				updateFunctions->update();
			}
		}

		void test2(float* resultStorage)
		{
			//delete most sources and add new ones (for memory fragmentation), see performance
			populateWithSources(5);
			populateWithObstacles(4);
			populateWithReceivers(10);
			populateWithSources(5);
			populateWithObstacles(4);
			populateWithReceivers(10); 
			populateWithSources(5);
			populateWithObstacles(4);
			populateWithSources(5);
			populateWithObstacles(4);
			populateWithSources(5);
			populateWithObstacles(4);
			populateWithSources(35);

			for (int i = 0; i < 10; i++)
			{
				listOfReceiversPtr->activate(2 * i);
				BasicMath::Timer timer(resultStorage + i);
				updateFunctions->update();
			}
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
			std::string logFileName = CreateNewPerformanceLogFile();
			
			float resultsStorage[10];
			for (int i = 0; i < 10; i++) { resultsStorage[i] = 0; }
			
			updateFunctions->resetLists();
			test0(resultsStorage);
			PrintToPerformanceLogFile(logFileName, "Test 0 - max lists capacity\nIndividual results:");
			PrintToPerformanceLogFile(logFileName, resultsStorage, 10);
			PrintToPerformanceLogFile(logFileName, "Average time: " + std::to_string(calculateMean(resultsStorage, 10)) + "\n");
			
			for (int i = 0; i < 10; i++) { resultsStorage[i] = 0; }

			updateFunctions->resetLists();
			test1(resultsStorage);
			PrintToPerformanceLogFile(logFileName, "Test 1 - some sources deleted\nIndividual results:");
			PrintToPerformanceLogFile(logFileName, resultsStorage, 10);
			PrintToPerformanceLogFile(logFileName, "Average time: " + std::to_string(calculateMean(resultsStorage, 10)) + "\n");
			
			for (int i = 0; i < 10; i++) { resultsStorage[i] = 0; }
			
			updateFunctions->resetLists();
			test2(resultsStorage);
			PrintToPerformanceLogFile(logFileName, "Test 2 - max capacity, memory fragmented\nIndividual results:");
			PrintToPerformanceLogFile(logFileName, resultsStorage, 10);
			PrintToPerformanceLogFile(logFileName, "Average time: " + std::to_string(calculateMean(resultsStorage, 10)) + "\n");

			PrintErrorLogToFile("End of performance test");

			updateFunctions->resetLists();
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
			if (quantity > 20)
			{
				return;
			}

			BasicMath::Point point[20];
			point[0].setPosX(0);
			point[0].setPosY(0);
			point[1].setPosX(0);
			point[1].setPosY(2);
			point[2].setPosX(2);
			point[2].setPosY(0);
			point[3].setPosX(10);
			point[3].setPosY(-5);
			point[4].setPosX(12);
			point[4].setPosY(0);
			point[5].setPosX(2);
			point[5].setPosY(20);
			point[6].setPosX(2);
			point[6].setPosY(4);
			point[7].setPosX(-2);
			point[7].setPosY(10);
			point[8].setPosX(-1);
			point[8].setPosY(1);
			point[9].setPosX(20);
			point[9].setPosY(-30);
			point[10].setPosX(5);
			point[10].setPosY(-8);
			point[11].setPosX(19);
			point[11].setPosY(-24);
			point[12].setPosX(-41);
			point[12].setPosY(22);
			point[13].setPosX(-31);
			point[13].setPosY(-25);
			point[14].setPosX(4.5);
			point[14].setPosY(-42);
			point[15].setPosX(43);
			point[15].setPosY(-14);
			point[16].setPosX(17.4);
			point[16].setPosY(-13.1);
			point[17].setPosX(5);
			point[17].setPosY(-40.3);
			point[18].setPosX(51.54);
			point[18].setPosY(0.73);
			point[19].setPosX(-1.3);
			point[19].setPosY(-22.7);
			for (int i = 0; i < quantity; i++)
			{
				listOfReceiversPtr->createReceiver(point[i].getPosX(), point[i].getPosY());
			}
		}

		float calculateMean(float* pointerToFirstElement, const unsigned int quantity)
		{
			float sum = 0;
			for (int i = 0; i < 10; i++)
			{
				sum = sum + pointerToFirstElement[i];
			}
			return sum / quantity;
		}
	}
}