#pragma once
#include "SoundAPI.h"
#include <string>
#include <fstream>

class SOUND_API SavingData 
{
public:
	SavingData();
	~SavingData();
	void saveAll(); // erase
	void saveAll(std::string fileName);

private:

	bool saveAllToBinFile(std::string& fileName);
	bool saveSources(std::ofstream& file);
	bool saveObstacles(std::ofstream& file);
	bool saveReceivers(std::ofstream& file);
};

extern SOUND_API SavingData* savingData;