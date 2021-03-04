#include "ErrorLogging.h"

#include <fstream>
#include <ctime>
#include <windows.h>

namespace ErrorLogging {

	static bool fileCreated = false;

	std::string getExecutableFilePath()
	{
		TCHAR buffer[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string path = buffer;
		for (int i = path.length(); i > 0; i--)
		{
			if (path[i] == '\\')
			{
				path.resize(i + 1); // won't overflow, no worries
				break;
			}
		}
		return path;
	}

	void PrintLogToFile(unsigned int severity, std::string &&message)
	{
		enum class MessageSeverity { Info=0, Warning, Error };
		MessageSeverity messageSeverity = MessageSeverity::Info;
		
		if (severity < 3)
			messageSeverity = static_cast<MessageSeverity>(severity);

		std::ofstream file;
		std::string filepath = getExecutableFilePath();
		if (fileCreated)
		{
			file.open(filepath + "Log.txt", std::ios::app);
		}
		else
		{
			file.open(filepath + "Log.txt");
			fileCreated = true;
		}

		switch (messageSeverity)
		{
		case MessageSeverity::Info:
			file << "[INFO]: " << message <<"\n";
			break;
		case MessageSeverity::Warning:
			file << "[WARNING]: " << message << "\n";
			break;
		case MessageSeverity::Error:
			file << "[ERROR]: " << message << "\n";
			break;
		default:
			file << "[DEFAULT]: " << message << "\n";
		}
		
		file.close();
	}
}