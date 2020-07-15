#pragma once
#include "SoundAPI.h"

class SOUND_API UpdateFunctions
{
public:
	UpdateFunctions();
	~UpdateFunctions();
	//All things that needs updating will be inside
	void update();
	void resetLists();
};

extern SOUND_API UpdateFunctions* updateFunctions;