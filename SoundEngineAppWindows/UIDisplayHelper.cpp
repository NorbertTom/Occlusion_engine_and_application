#include "UIDisplayHelper.h"

namespace UIDisplayHelper
{
	std::string toString(float value, int precision)
	{
		std::string tempString = std::to_string(value);
		int dotPosition = 0;
		for (int i = 0; i < tempString.length(); i++)
		{
			if (tempString[i] == '.')
			{
				dotPosition = i;
			}
			if (i > dotPosition + precision)
			{
				tempString[i] = NULL;
				i = tempString.length();
			}
		}
		tempString.resize(dotPosition + precision + 2);
		return tempString;
	}

	std::string toString(float value)
	{
		return toString(value, 2);
	}

	std::string toString(bool value)
	{
		std::string returnString;
		if (value == true)
		{
			returnString = "true";
		}
		else
		{
			returnString = "false";
		}
		return returnString;
	}

	std::string toString(int value)
	{
		return std::to_string(value);
	}

	bool convertStringToValidNumber(std::string& string)
	{
		if (string.length() == 0)
		{
			return false;
		}

		bool validFloat = true;
		bool hasDot = false;
		for (int i = 0; i < string.length(); i++)
		{
			if (string[i] == '0' || string[i] == '1' || string[i] == '2' || string[i] == '3'
				|| string[i] == '4' || string[i] == '5' || string[i] == '6' || string[i] == '7'
				|| string[i] == '8' || string[i] == '9')
			{}
			else if (string[i] == '.')
			{
				if (hasDot)
				{
					i = string.length();
					validFloat = false;
				}
				else
				{
					hasDot = true;
				}
			}
			else if (string[i] == ',')
			{
				if (hasDot)
				{
					i = string.length();
					validFloat = false;
				}
				else
				{
					string[i] = '.';
					hasDot = true;
				}
			}
			else if (string[i] == '-')
			{
				if (i != 0)
				{
					i = string.length();
					validFloat = false;
				}
			}
			else
			{
				i = string.length();
				validFloat = false;
			}
		}
		return validFloat;
	}

	bool isValidString(std::string& string)
	{
		bool result = string.length() == 0 ? false : true;

		for (int i = 0; i < string.length(); i++)
		{
			int intFromChar = static_cast<int>(string[i]);
			if ((intFromChar > 47 && intFromChar < 58)
				|| (intFromChar > 64 && intFromChar < 91)
				|| (intFromChar > 96 && intFromChar < 123))
			{}
			else
			{
				result = false;
				i = string.length();
			}
		}
		return result;
	}
}