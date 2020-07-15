#include "SoundEngineAppWindows.h"
#include "SoundEngineMainWindow.h"

wxIMPLEMENT_APP(SoundEngineAppWindows);

SoundEngineAppWindows::SoundEngineAppWindows()
{
}


SoundEngineAppWindows::~SoundEngineAppWindows()
{
}

bool SoundEngineAppWindows::OnInit()
{
	mainWindow = new SoundEngineMainWindow();
	mainWindow->Show();
	return true;
}