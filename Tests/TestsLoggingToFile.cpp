#include "Tests.h"

#include <fstream>


namespace Tests
{
	static bool TestsLogFileCreated = false;

	void PrintErrorLogToFile(std::string message)
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

}