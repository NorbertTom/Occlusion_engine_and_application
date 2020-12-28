#pragma once

#include <string>

#define LOG_INFO(x) ErrorLogging::PrintLogToFile (0, x)
#define LOG_WARNING(x) ErrorLogging::PrintLogToFile (1, x)
#define LOG_ERROR(x) ErrorLogging::PrintLogToFile (2, x)


namespace ErrorLogging {

	void PrintLogToFile(unsigned int severity, std::string &&message);

}