#include "Tests.h"

#include <fstream>
#include <io.h>
#include <chrono>
#include <ctime>
#include "PerformanceDefines.h"

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

	std::string CreateNewPerformanceLogFile()
	{
		return CreateNewPerformanceLogFile("");
	}

	std::string CreateNewPerformanceLogFile(std::string &&message)
	{
		char* bufTime = new char[26];
		auto timeNow = std::chrono::system_clock::now();
		std::time_t timeNow_time_t = std::chrono::system_clock::to_time_t(timeNow);
		ctime_s(bufTime, 26, &timeNow_time_t);
		std::string timeStr = bufTime;
		delete[] bufTime;
		timeStr.resize(timeStr.size() - 1);
		for (int i = 0; i < timeStr.length(); i++)
		{
			if (timeStr[i] == ' ' || timeStr[i] == ':')
			{
				timeStr[i] = '_';
			}
		}
		
		std::string fileName = "!PerformanceLog_";
		fileName += timeStr;
		fileName += ".txt";

		// about configuration
		std::string configuration = "Configuration = ";
		configuration += CONFIGURATION;
		configuration += "\n";

		std::string memoryPoolOptions;
#ifdef SourcesUsingNorMemoryPool
		memoryPoolOptions += "Using Sources Memory Pool;\n";
#endif
#ifdef ObstaclesUsingNorMemoryPool
		memoryPoolOptions += "Using Obstacles Memory Pool;\n";
#endif
#ifdef ReceiversUsingNorMemoryPool
		memoryPoolOptions += "Using Receivers Memory Pool;\n";
#endif
		std::string otherOptions = "";

		// ----

		std::ofstream file;
		file.open(fileName);
		file << configuration << memoryPoolOptions << otherOptions << message << "\n\n";
		file.close();
		return fileName;
	}

	void PrintToPerformanceLogFile(std::string& fileName, const float* firstNumber, const unsigned int quantity)
	{
		std::ofstream file;
		file.open(fileName.c_str(), std::ios::app);
		
		for (int i = 0; i < quantity; i++)
		{
			file << *(firstNumber+i) << ", ";
		}
		file << "\n";
		
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