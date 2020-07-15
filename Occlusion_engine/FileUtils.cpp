#include "FileUtils.h"
#include <iostream>

namespace FileUtils
{

	void addExtensionToFilename(std::string& filename)
	{
		if (filename.length() < 5)
		{
			filename = filename + ".bin";
		}
		else
		{
			char ending[4];
			for (int i = 0; i < 4; i++)
			{
				ending[i] = filename[filename.length() + (i - 4)];
			}
			if (ending[0] == '.' && ending[1] == 'b' && ending[2] == 'i' && ending[3] == 'n')
			{
			}
			else
			{
				filename = filename + ".bin";
			}
		}
	}
}