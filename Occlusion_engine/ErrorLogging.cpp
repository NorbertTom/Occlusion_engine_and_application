#include "ErrorLogging.h"

#include <fstream>
#include <ctime>

namespace ErrorLogging {

	static bool fileCreated = false;

	void PrintLogToFile(unsigned int severity, std::string message)
	{
		enum class MessageSeverity { Info=0, Warning, Error };
		MessageSeverity messageSeverity;
		
		if (severity < 3)
			messageSeverity = static_cast<MessageSeverity>(severity);

		std::ofstream file;

		if (fileCreated)
		{
			file.open("Log.txt", std::ios::app);
		}
		else
		{
			file.open("Log.txt");
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