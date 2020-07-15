#pragma once
#include <string>

namespace UIDisplayHelper
{
	std::string toString(float value, int precision);
	std::string toString(float value);
	std::string toString(bool value);
	std::string toString(int value);

	bool convertStringToValidNumber(std::string& string);
	bool isValidString(std::string& string);

}