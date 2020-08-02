#include <string>
#include "SoundEngineMainWindow.h"
#include "SoundAPI.h"

#include "ListOfObstacles.h"
#include "Obstacle.h"
#include "PopupObstacle.h"

void SoundEngineMainWindow::onUIlistOfObstaclesSelect(wxListEvent& event)
{
	buttonObstacleEdit->Enable();
	buttonObstacleDelete->Enable();
	event.Skip();
}

void SoundEngineMainWindow::onUIlistOfObstaclesDclick(wxListEvent& event)
{
	onButtonClickedObstacleEdit(event); // ryzykowne
	event.Skip();
}

void SoundEngineMainWindow::onUIlistOfObstaclesDeselect(wxListEvent& event)
{
	buttonObstacleEdit->Disable();
	buttonObstacleDelete->Disable();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedObstacleAdd(wxCommandEvent & event)
{
	PopupObstacle* popupObstacle = new PopupObstacle(this, "Add");
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedObstacleEdit(wxCommandEvent & event)
{
	int selected = UIlistOfObstacles->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	int obstacleId = std::stoi(static_cast<std::string>(UIlistOfObstacles->GetItemText(selected, 0)));
	Obstacle* obstaclePtr = listOfObstaclesPtr->getPtrById(obstacleId);
	ObstacleDetails obstacleDetails	(
		obstaclePtr,
		obstaclePtr->getPosX1(),
		obstaclePtr->getPosY1(),
		obstaclePtr->getPosX2(),
		obstaclePtr->getPosY2(),
		obstaclePtr->getDampening()	);
	PopupObstacle* popupObstacle = new PopupObstacle(this, "Edit", obstacleDetails);
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedObstacleDelete(wxCommandEvent & event)
{
	int selected = UIlistOfObstacles->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	int selectedId = std::stoi(static_cast<std::string>(UIlistOfObstacles->GetItemText(selected, 0)));
	listOfObstaclesPtr->deleteObstacleById(selectedId);
	refreshWindow();
	event.Skip();
}

void SoundEngineMainWindow::onButtonClickedObstacleDeleteAll(wxCommandEvent & event)
{
	listOfObstaclesPtr->deleteAll();
	refreshWindow();
	event.Skip();
}

