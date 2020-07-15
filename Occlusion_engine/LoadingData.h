#pragma once
#include "SoundAPI.h"
#include <fstream>

class SOUND_API LoadingData
{
public:
	LoadingData();
	~LoadingData();
	bool loadDataFromFile(std::string& fileName);
	bool wasLoadingSuccessfull();

private:

	bool loadingSuccess = false;
	bool loadSourcesSuccess = false;
	bool loadObstaclesSuccess = false;
	bool loadReceiversSuccess = false;

	bool loadSources(std::ifstream& file);
	bool loadObstacles(std::ifstream& file);
	bool loadReceivers(std::ifstream& file);

};

extern SOUND_API LoadingData* loadingData;