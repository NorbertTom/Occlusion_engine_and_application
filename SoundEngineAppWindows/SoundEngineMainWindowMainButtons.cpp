#include "SoundEngineMainWindow.h"
#include "SoundAPI.h"

#include "LoadingData.h"
#include "UpdateFunctions.h"
#include "PopupLoadSave.h"
#include "Receiver.h"
#include "ListOfReceivers.h"

// ---------------- MAIN BUTTONS --------------------------

void SoundEngineMainWindow::onButtonClickedExit(wxCommandEvent& event)
{
	this->Close();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedClearSelection(wxCommandEvent& event)
{
	refreshWindow();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedLoad(wxCommandEvent& event)
{
	PopupLoadSave* loadSaveWindow = new PopupLoadSave(this, true);
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedSave(wxCommandEvent& event)
{
	PopupLoadSave* loadSaveWindow = new PopupLoadSave(this, false); 
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedGoUp(wxCommandEvent& event)
{
	MoveReceiverDirection direction = MoveReceiverDirection::Up;
	if (Receiver* activeReceiver = listOfReceiversPtr->getActive())
	{
		activeReceiver->moveReceiver(direction);
	}
	else
	{
		//no active receiver, do nothing, prevents crash
	}
	refreshWindow();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedGoLeft(wxCommandEvent& event)
{
	MoveReceiverDirection direction = MoveReceiverDirection::Left;
	if (Receiver* activeReceiver = listOfReceiversPtr->getActive())
	{
		activeReceiver->moveReceiver(direction);
	}
	else
	{
		//no active receiver, do nothing, prevents crash
	}
	refreshWindow();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedGoDown(wxCommandEvent& event)
{
	MoveReceiverDirection direction = MoveReceiverDirection::Down;
	if (Receiver* activeReceiver = listOfReceiversPtr->getActive())
	{
		activeReceiver->moveReceiver(direction);
	}
	else
	{
		//no active receiver, do nothing, prevents crash
	}
	refreshWindow();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedGoRight(wxCommandEvent& event)
{
	MoveReceiverDirection direction = MoveReceiverDirection::Right;
	if (Receiver* activeReceiver = listOfReceiversPtr->getActive())
	{
		activeReceiver->moveReceiver(direction);
	}
	else
	{
		//no active receiver, do nothing, prevents crash
	}
	refreshWindow();
	event.Skip();
}