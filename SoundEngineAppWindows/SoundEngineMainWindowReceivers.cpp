#include "SoundEngineMainWindow.h"
#include "PopupWindowSmall.h"
#include "SoundAPI.h"

#include "PopupReceiver.h"
#include "ListOfReceivers.h"
#include "Receiver.h"

void SoundEngineMainWindow::onUIlistOfReceiversSelect(wxListEvent& event)
{
	buttonReceiverEdit->Enable();
	buttonReceiverDelete->Enable();
	event.Skip();
}

void SoundEngineMainWindow::onUIlistOfReceiversDclick(wxListEvent& event)
{
	onButtonClickedReceiverEdit(event);
	event.Skip();
}

void SoundEngineMainWindow::onUIlistOfReceiversDeselect(wxListEvent& event)
{
	buttonReceiverEdit->Disable();
	buttonReceiverDelete->Disable();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedReceiverAdd(wxCommandEvent & event)
{
	PopupReceiver* popupReceiver = new PopupReceiver(this, "Add");
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedReceiverEdit(wxCommandEvent & event)
{
	int selected = UIlistOfReceivers->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	int receiverId = std::stoi(static_cast<std::string>(UIlistOfReceivers->GetItemText(selected, 0)));
	Receiver* receiverPtr = listOfReceiversPtr->getPtrById(receiverId);
	ReceiverDetails receiverDetails(
		receiverPtr,
		receiverPtr->getPosX(),
		receiverPtr->getPosY(),
		receiverPtr->ifActive());
	PopupReceiver* popupReceiver = new PopupReceiver(this, "Edit", receiverDetails);
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedReceiverDelete(wxCommandEvent & event)
{
	int selected = UIlistOfReceivers->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	int selectedId = std::stoi(static_cast<std::string>(UIlistOfReceivers->GetItemText(selected, 0)));
	if (listOfReceiversPtr->getActive()->getId() == selectedId)
	{
		std::string title = "Error";
		std::string message = "Can't delete active Receiver!";
		PopupWindowSmall* popup = new PopupWindowSmall(static_cast<wxWindow*>(this), title, message);
	}
	else
	{
		listOfReceiversPtr->deleteReceiverById(selectedId);
		refreshWindow();
	}
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedReceiverDeleteAll(wxCommandEvent & event)
{
	listOfReceiversPtr->deleteAll();
	refreshWindow();
	event.Skip();
}