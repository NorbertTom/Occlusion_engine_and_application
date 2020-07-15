#pragma once
#include "wx\wx.h"

class SoundEngineMainWindow;

class SoundEngineAppWindows : public wxApp
{
public:
	SoundEngineAppWindows();
	~SoundEngineAppWindows();

	virtual bool OnInit();

	SoundEngineMainWindow* mainWindow = nullptr;
};

