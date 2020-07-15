#include "Tests.h"

namespace Test {

	void DeleteAll();

	

		void main()
		{
			std::cout << "Testing if occlusion works...\n";
			bool testIsSoundSourceOccludedByObstacleResult[10];
			for (int i = 0; i < sizeof(testIsSoundSourceOccludedByObstacleResult); i++)
				testIsSoundSourceOccludedByObstacleResult[i] = false;

			int failCounter = 0;
			testIsSoundSourceOccludedByObstacleResult[0] = testIsSoundSourceOccludedByObstacle::test0(failCounter);
			DeleteAll();
			testIsSoundSourceOccludedByObstacleResult[1] = testIsSoundSourceOccludedByObstacle::test1(failCounter);
			DeleteAll();
			testIsSoundSourceOccludedByObstacleResult[2] = testIsSoundSourceOccludedByObstacle::test2(failCounter);
			DeleteAll();
			testIsSoundSourceOccludedByObstacleResult[3] = testIsSoundSourceOccludedByObstacle::test3(failCounter);
			DeleteAll();
			testIsSoundSourceOccludedByObstacleResult[4] = testIsSoundSourceOccludedByObstacle::test4(failCounter);
			DeleteAll();
			testIsSoundSourceOccludedByObstacleResult[5] = testIsSoundSourceOccludedByObstacle::test5(failCounter);
			DeleteAll();
			testIsSoundSourceOccludedByObstacleResult[6] = testIsSoundSourceOccludedByObstacle::test6(failCounter);
			DeleteAll();
			testIsSoundSourceOccludedByObstacleResult[7] = testIsSoundSourceOccludedByObstacle::test7(failCounter);
			DeleteAll();
			testIsSoundSourceOccludedByObstacleResult[8] = testIsSoundSourceOccludedByObstacle::test8(failCounter);
			DeleteAll();
			testIsSoundSourceOccludedByObstacleResult[9] = testIsSoundSourceOccludedByObstacle::test9(failCounter);
			DeleteAll();
			int nrOfTests = sizeof(testIsSoundSourceOccludedByObstacleResult);
			std::cout << "Is Sound Source Occluded By Obstacle Tests passed: " << nrOfTests - failCounter << "/" << nrOfTests << "\n";
			if (failCounter > 0)
				printFailed(testIsSoundSourceOccludedByObstacleResult, sizeof(testIsSoundSourceOccludedByObstacleResult));


		}
	}
	/*
	bool testIfObstacleListWorks::test0()
	{
		//If creating new Obstacles works good
		BasicMath::Timer timer;
		const int amount = 10;
		for (int i = 0; i < amount; i++)
			new Obstacle(i, i + 2, i + 1, i + 3);
		int ObstacleQuantity = Obstacle::GetObstacleAmount();
		Obstacle::DeleteAll();
		if (ObstacleQuantity == 10)
			return true;
		else
		{
			failCounter++;
			return false;
		}
	}

	bool testIfObstacleListWorks::test1()
	{
		//If deleting works good
		BasicMath::Timer timer;
		const int amount = 20;
		for (int i = 0; i < amount; i++)
			new Obstacle(i, i + 2, i + 1, i + 3);
		for (int i = 10; i > 0; i--)
			delete *(Obstacle::GetListOfObstacles() + i);
		int ObstacleQuantity = Obstacle::GetObstacleAmount();
		Obstacle::DeleteAll();
		if (ObstacleQuantity == 10)
			return true;
		else
		{
			failCounter++;
			return false;
		}
	}

	bool testIfObstacleListWorks::test2()
	{
		//If deleting and creating works good
		BasicMath::Timer timer;
		int amount = 20;
		for (int i = 0; i < amount; i++)
			new Obstacle(i, i + 2, i + 1, i + 3);
		for (int i = 10; i > 0; i--)
			delete *(Obstacle::GetListOfObstacles() + i);
		amount = 30;
		for (int i = 0; i < amount; i++)
			new Obstacle(i, i + 2, i + 1, i + 3);
		for (int i = 5; i > 0; i--)
			delete *(Obstacle::GetListOfObstacles() + i);
		int ObstacleQuantity = Obstacle::GetObstacleAmount();
		Obstacle::DeleteAll();
		if (ObstacleQuantity == 35)
			return true;
		else
		{
			failCounter++;
			return false;
		}

		failCounter++;
		return false;
	}

	bool testIfObstacleListWorks::test3()
	{
		//If DeleteAll works
		BasicMath::Timer timer;
		for (int i = 0; i < 60; i++)
			new Obstacle(1, 2, 3, 4);
		Obstacle::DeleteAll();
		for (int i = 0; i < 100; i++)
		{
			if (*(Obstacle::GetListOfObstacles() + i) != nullptr)
			{
				failCounter++;
				return false;
			}
		}
		return true;
	}

	testIfObstacleListWorks::testIfObstacleListWorks()
	{
		std::cout << "Testing if Obstacle list works...\n";
		for (int i = 0; i < sizeof(testPassed); i++)
			testPassed[i] = false;
		testPassed[0] = test0();
		testPassed[1] = test1();
		testPassed[2] = test2();
		testPassed[3] = test3();
		int nrOfTests = sizeof(testPassed);
		std::cout << "If Obstacle List Works tests passed: " << nrOfTests - failCounter << "/" << nrOfTests << "\n";
		if (failCounter > 0)
			printFailed(testPassed, sizeof(testPassed));
	}

	testIfObstacleListWorks::~testIfObstacleListWorks()
	{
		clearAll();
	}

	bool testIfSoundSourceListWorks::test0()
	{
		//If creating new Obstacles works good
		BasicMath::Timer timer;
		const int amount = 10;
		for (int i = 0; i < amount; i++)
			new SoundSource(i, i + 2);
		int SourcesQuantity = SoundSource::GetSoundSourcesAmount();
		SoundSource::DeleteAll();
		if (SourcesQuantity == 10)
			return true;
		else
		{
			failCounter++;
			return false;
		}
	}

	bool testIfSoundSourceListWorks::test1()
	{
		//If deleting works good
		BasicMath::Timer timer;
		const int amount = 20;
		for (int i = 0; i < amount; i++)
			new SoundSource(i, 2 * i + 5);
		for (int i = 10; i > 0; i--)
			delete *(SoundSource::GetListOfSoundSources() + i);
		int SourcesQuantity = SoundSource::GetSoundSourcesAmount();
		SoundSource::DeleteAll();
		if (SourcesQuantity == 10)
			return true;
		else
		{
			failCounter++;
			return false;
		}
	}

	bool testIfSoundSourceListWorks::test2()
	{
		//If deleting and creating works good
		BasicMath::Timer timer;
		int amount = 20;
		for (int i = 0; i < amount; i++)
			new SoundSource(i + 2, i, 85);
		for (int i = 10; i > 0; i--)
			delete *(SoundSource::GetListOfSoundSources() + i);
		amount = 30;
		for (int i = 0; i < amount; i++)
			new SoundSource(i - 2, i + 5);
		for (int i = 5; i > 0; i--)
			delete *(SoundSource::GetListOfSoundSources() + i);
		int SourcesQuantity = SoundSource::GetSoundSourcesAmount();
		SoundSource::DeleteAll();
		if (SourcesQuantity == 35)
			return true;
		else
		{
			failCounter++;
			return false;
		}

		failCounter++;
		return false;
	}

	bool testIfSoundSourceListWorks::test3()
	{
		//If DeleteAll works
		BasicMath::Timer timer;
		for (int i = 0; i < 60; i++)
			new SoundSource(1, 2);
		SoundSource::DeleteAll();
		for (int i = 0; i < 100; i++)
		{
			if (*(SoundSource::GetListOfSoundSources() + i) != nullptr)
			{
				failCounter++;
				return false;
			}
		}
		return true;
	}

	testIfSoundSourceListWorks::testIfSoundSourceListWorks()
	{
		std::cout << "Testing if SoundSource list works...\n";
		for (int i = 0; i < sizeof(testPassed); i++)
			testPassed[i] = false;
		testPassed[0] = test0();
		testPassed[1] = test1();
		testPassed[2] = test2();
		testPassed[3] = test3();
		int nrOfTests = sizeof(testPassed);
		std::cout << "If SoundSource List Works tests passed: " << nrOfTests - failCounter << "/" << nrOfTests << "\n";
		if (failCounter > 0)
			printFailed(testPassed, sizeof(testPassed));
	}

	testIfSoundSourceListWorks::~testIfSoundSourceListWorks()
	{
		clearAll();
	}

	bool testSetCurrentAttenuationOnSources::test0()
	{
		//Smoketest ;)
		BasicMath::Timer timer;
		Receiver::CreateReceiver(0, 0);
		Receiver* listener = Receiver::getReceiverInstance();
		SoundSource* source1 = new SoundSource(10, 10);
		SoundSource* source2 = new SoundSource(0, 2);
		SoundSource* source3 = new SoundSource(-15, 0);
		SoundSource* source4 = new SoundSource(-5, -2);
		SoundSource* source5 = new SoundSource(10, 0);
		listener->SetCurrentAttenuationOnSources();
		delete listener;
		for (int i = 0; i < SoundSource::GetSoundSourcesAmount(); i++)
		{
			if ((*(SoundSource::GetListOfSoundSources() + i))->currentAttenuation != 0)
			{
				failCounter++;
				return false;
			}
		}
		return true;
	}

	bool testSetCurrentAttenuationOnSources::test1()
	{
		//Checking if Att is correctly assigned to corresponding source
		BasicMath::Timer timer;
		Receiver::CreateReceiver(0, 0);
		Receiver* listener = Receiver::getReceiverInstance();
		SoundSource* source1 = new SoundSource(3, 10);
		SoundSource* source2 = new SoundSource(2, 7);
		SoundSource* source3 = new SoundSource(-15, 0);
		SoundSource* source4 = new SoundSource(-50, -2);
		SoundSource* source5 = new SoundSource(10, 0);
		listener->SetCurrentAttenuationOnSources();
		delete listener;
		for (int i = 0; i < 3; i++)
		{
			if ((*(SoundSource::GetListOfSoundSources() + i))->currentAttenuation != 0)
			{
				failCounter++;
				return false;
			}
		}
		if ((*(SoundSource::GetListOfSoundSources() + 3))->currentAttenuation == 0)
		{
			failCounter++;
			return false;
		}
		else if ((*(SoundSource::GetListOfSoundSources() + 4))->currentAttenuation != 0)
		{
			failCounter++;
			return false;
		}
		else
			return true;
	}

	bool testSetCurrentAttenuationOnSources::test2()
	{
		//Creating and deleting sources test, very close to listener (att should =0)
		BasicMath::Timer timer;
		Receiver::CreateReceiver(0, 0);
		Receiver* listener = Receiver::getReceiverInstance();
		for (int i = 0; i < 60; i++)
			new SoundSource(0, 0);
		for (int i = 0; i < 20; i++)
			delete (*(SoundSource::GetListOfSoundSources() + i));
		for (int i = 0; i < 30; i++)
			new SoundSource(10, 10);
		listener->SetCurrentAttenuationOnSources();
		delete listener;
		for (int i = 0; i < SoundSource::GetSoundSourcesAmount(); i++)
		{
			if ((*(SoundSource::GetListOfSoundSources() + i))->currentAttenuation != 0)
			{
				failCounter++;
				return false;
			}
		}
		return true;
	}

	bool testSetCurrentAttenuationOnSources::test3()
	{
		//If each dampening is calculated correctly with each source + receiver weird position
		BasicMath::Timer timer;
		Receiver::CreateReceiver(100, 100);
		Receiver* listener = Receiver::getReceiverInstance();
		new SoundSource(120, 100);
		new SoundSource(100, 120);
		new SoundSource(80, 90);
		new Obstacle(110, 80, 110, 120, 21);
		new Obstacle(90, 105, 113, 109, 11);
		new Obstacle(80, 100, 90, 81, 7);
		listener->SetCurrentAttenuationOnSources();
		delete listener;
		if ((*(SoundSource::GetListOfSoundSources()))->currentAttenuation == (*(Obstacle::GetListOfObstacles()))->GetDampening()
			&& (*(SoundSource::GetListOfSoundSources() + 1))->currentAttenuation == (*(Obstacle::GetListOfObstacles() + 1))->GetDampening()
			&& (*(SoundSource::GetListOfSoundSources() + 2))->currentAttenuation == (*(Obstacle::GetListOfObstacles() + 2))->GetDampening())
			return true;
		else
		{
			failCounter++;
			return false;
		}
	}

	bool testSetCurrentAttenuationOnSources::test4()
	{
		//If dampenings do sum up
		BasicMath::Timer timer;
		Receiver::CreateReceiver(10, 10);
		Receiver* listener = Receiver::getReceiverInstance();
		SoundSource* source1 = new SoundSource(40, 10);
		SoundSource* source2 = new SoundSource(-20, -5);
		Obstacle* mur1 = new Obstacle(20, 20, 21, 0, 10);
		Obstacle* mur2 = new Obstacle(30, 25, 29, 9, 11);
		Obstacle* mur3 = new Obstacle(-20, 10, 10, -20, 7);
		Obstacle* mur4 = new Obstacle(-10, 10, 5, -8, 9);
		listener->SetCurrentAttenuationOnSources();
		delete listener;
		if (source1->currentAttenuation > (mur1->GetDampening() + mur2->GetDampening())
			&& source2->currentAttenuation > (mur3->GetDampening() + mur4->GetDampening()))
			return true;
		else
		{
			failCounter++;
			return false;
		}
	}

	testSetCurrentAttenuationOnSources::testSetCurrentAttenuationOnSources()
	{
		//re-work this as cm switched to m as a units of this program
		std::cout << "Testing SetCurrentAttenuationOnSources method...\n";
		for (int i = 0; i < sizeof(testPassed); i++)
			testPassed[i] = false;
		testPassed[0] = test0();
		clearAll();
		testPassed[1] = test1();
		clearAll();
		testPassed[2] = test2();
		clearAll();
		testPassed[3] = test3();
		clearAll();
		testPassed[4] = test4();
		clearAll();
		int nrOfTests = sizeof(testPassed);
		std::cout << "If SoundSource List Works tests passed: " << nrOfTests - failCounter << "/" << nrOfTests << "\n";
		if (failCounter > 0)
			printFailed(testPassed, sizeof(testPassed));

	}

	testSetCurrentAttenuationOnSources::~testSetCurrentAttenuationOnSources()
	{
		clearAll();
	}

	*/
	void printFailed(bool* testPassed, int size)
	{
		for (int i = 0; i < size; i++)
		{
			if (!*(testPassed + i))
				std::cout << "Test " << i << " not passed\n";
		}
	}

	void runAllAvailableTests()
	{
		std::cout << "Testing started!\n\n";
		testIsSoundSourceOccludedByObstacle::main();
		//I reszta podobnie
		/*if (auto test = new testIfObstacleListWorks())
			delete test;
		if (auto test = new testIfSoundSourceListWorks())
			delete test;
		if (auto test = new testSetCurrentAttenuationOnSources())
			delete test;*/
	}
	
	void DeleteAll()
	{
		SoundSource::DeleteAll();
		Obstacle::DeleteAll();
		Receiver::DeleteReceiver();
	}
}