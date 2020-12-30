#include "Tests.h"

#include <fstream>
#include <io.h>


namespace Tests
{
	static bool TestsLogFileCreated = false;

	void PrintErrorLogToFile(std::string &&message)
	{
		std::ofstream file;

		if (TestsLogFileCreated)
		{
			file.open("!TestsLog.txt", std::ios::app);
		}
		else
		{
			file.open("!TestsLog.txt");
			TestsLogFileCreated = true;
		}
		
		file << message << "\n";
		file.close();
	}

	std::string CreateNewPerformanceLogFile(std::string &&message)
	{
		std::string rootFileName = "!PerformanceLog_";
		std::string extension = ".txt";
		int iterator = 0;
		std::string workingName = rootFileName + std::to_string(iterator) + extension;
		while (_access(workingName.c_str(), 0) == 0)
		{
			iterator++;
			workingName = rootFileName + std::to_string(iterator) + extension;
			if (iterator == 20)
			{
				for (int i = 0; i < iterator; i++)
				{
					workingName = rootFileName + std::to_string(i) + extension;
					remove(workingName.c_str());
				}
				iterator = 0;
			}
		}

		std::ofstream file;
		file.open(workingName);
		file << message << "\n\n";
		file.close();
		return workingName;
	}

	void PrintToPerformanceLogFile(std::string& fileName, const float* firstNumber, const unsigned int quantity)
	{
		std::ofstream file;
		file.open(fileName.c_str(), std::ios::app);
		
		for (int i = 0; i < quantity; i++)
		{
			file << *(firstNumber+i) << "\n";
		}
		
		file.close();
	}

	void PrintToPerformanceLogFile(std::string& fileName, std::string &&message)
	{
		std::ofstream file;
		file.open(fileName.c_str(), std::ios::app);
		file << message << "\n";
		file.close();
	}
}