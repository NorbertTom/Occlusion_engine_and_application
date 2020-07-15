#include <string>
#include "SoundEngineMainWindow.h"
#include "SoundAPI.h"
#include "PopupSource.h"
#include "ListOfSources.h"
#include "SoundSource.h"

// ------------------ SOURCE ------------------

void SoundEngineMainWindow::onUIlistOfSourcesSelect(wxListEvent& event)
{
	buttonSourceEdit->Enable();
	buttonSourceDelete->Enable();
	event.Skip();
}

void SoundEngineMainWindow::onUIlistOfSourcesDclick(wxListEvent& event)
{
	onButtonClickedSourceEdit(event);
	event.Skip();
}

void SoundEngineMainWindow::onUIlistOfSourcesDeselect(wxListEvent& event)
{
	buttonSourceEdit->Disable();
	buttonSourceDelete->Disable();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedSourceAdd(wxCommandEvent & event)
{
	PopupSource* popupSource = new PopupSource(this, "Add");
	popupSource->Show();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedSourceEdit(wxCommandEvent & event)
{
	int selected = UIlistOfSources->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	int sourceId = std::stoi(static_cast<std::string>(UIlistOfSources->GetItemText(selected, 0)));
	SoundSource* sourcePtr = listOfSourcesPtr->getPtrById(sourceId);
	SourceDetails sourceDetails(
		sourcePtr,
		sourcePtr->getPosX(),
		sourcePtr->getPosY(),
		sourcePtr->getLwa(),
		sourcePtr->getMaxDistance(),
		sourcePtr->ifOccludable(),
		sourcePtr->getAttenuationType());
	PopupSource* popupSource = new PopupSource(this, "Edit", sourceDetails);
	popupSource->Show();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedSourceDelete(wxCommandEvent & event)
{
	int selected = UIlistOfSources->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	int selectedId = std::stoi(static_cast<std::string>(UIlistOfSources->GetItemText(selected, 0)));
	listOfSourcesPtr->deleteSourceById(selectedId);
	refreshWindow();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedSourceDeleteAll(wxCommandEvent & event)
{
	listOfSourcesPtr->deleteAll();
	refreshWindow();
	event.Skip();
}
