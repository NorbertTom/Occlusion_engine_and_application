#include <string>
#include "SoundEngineMainWindow.h"

#include "SoundAPI.h"
#include "SoundEngineInitializer.h"

wxBEGIN_EVENT_TABLE(SoundEngineMainWindow, wxFrame)
	EVT_BUTTON(666, onButtonClickedExit)
	EVT_BUTTON(665, onButtonClickedClearSelection)
	EVT_BUTTON(664, onButtonClickedLoad)
	EVT_BUTTON(663, onButtonClickedSave)

	EVT_BUTTON(700, onButtonClickedGoUp)
	EVT_BUTTON(701, onButtonClickedGoLeft)
	EVT_BUTTON(702, onButtonClickedGoDown)
	EVT_BUTTON(703, onButtonClickedGoRight)

	EVT_BUTTON(101, onButtonClickedSourceAdd)
	EVT_BUTTON(102, onButtonClickedSourceEdit)
	EVT_BUTTON(103, onButtonClickedSourceDelete)
	EVT_BUTTON(104, onButtonClickedSourceDeleteAll)
	EVT_BUTTON(201, onButtonClickedObstacleAdd)
	EVT_BUTTON(202, onButtonClickedObstacleEdit)
	EVT_BUTTON(203, onButtonClickedObstacleDelete)
	EVT_BUTTON(204, onButtonClickedObstacleDeleteAll)
	EVT_BUTTON(301, onButtonClickedReceiverAdd)
	EVT_BUTTON(302, onButtonClickedReceiverEdit)
	EVT_BUTTON(303, onButtonClickedReceiverDelete)
	EVT_BUTTON(304, onButtonClickedReceiverDeleteAll)
	
	EVT_LIST_ITEM_SELECTED(100, onUIlistOfSourcesSelect)
	EVT_LIST_ITEM_ACTIVATED(100, onUIlistOfSourcesDclick)
	EVT_LIST_ITEM_DESELECTED(100, onUIlistOfSourcesDeselect)
	EVT_LIST_ITEM_SELECTED(200, onUIlistOfObstaclesSelect)
	EVT_LIST_ITEM_ACTIVATED(200, onUIlistOfObstaclesDclick)
	EVT_LIST_ITEM_DESELECTED(200, onUIlistOfObstaclesDeselect)
	EVT_LIST_ITEM_SELECTED(300, onUIlistOfReceiversSelect)
	EVT_LIST_ITEM_ACTIVATED(300, onUIlistOfReceiversDclick)
	EVT_LIST_ITEM_DESELECTED(300, onUIlistOfReceiversDeselect)
	
	EVT_LIST_COL_BEGIN_DRAG(100, onColumnDrag)
	EVT_LIST_COL_BEGIN_DRAG(200, onColumnDrag)
	EVT_LIST_COL_BEGIN_DRAG(300, onColumnDrag)

	EVT_ACTIVATE(refreshWindowEvent)
	
wxEND_EVENT_TABLE()

SoundEngineMainWindow::SoundEngineMainWindow() 
	: wxFrame(nullptr, 0, "SoundEngine Main Window", wxPoint(450, 150), wxSize(880, 800))
{
	SoundEngineInitializer::initialize();
	
	labelSources = new wxStaticText(this, wxID_ANY, "Sources:", wxPoint(10, 10), wxSize(100, 20));
	UIlistOfSources = new wxListCtrl(this, 100, wxPoint(10, 40), wxSize(830, 200), wxLC_SINGLE_SEL + wxLC_REPORT);
	createColumns(UIlistOfSources);

	buttonSourceAdd = new wxButton(this, 101, "Add", wxPoint(10, 250), wxSize(70, 30));
	buttonSourceEdit = new wxButton(this, 102, "Edit", wxPoint(85, 250), wxSize(70, 30));
	buttonSourceDelete = new wxButton(this, 103, "Delete", wxPoint(160, 250), wxSize(70, 30));
	buttonSourceDeleteAll = new wxButton(this, 104, "Delete All", wxPoint(235, 250), wxSize(70, 30));
	
	labelObstacles = new wxStaticText(this, wxID_ANY, "Obstacles:", wxPoint(10, 360), wxSize(100, 20));
	UIlistOfObstacles = new wxListCtrl(this, 200, wxPoint(10, 400), wxSize(350, 200), wxLC_SINGLE_SEL + wxLC_REPORT);
	createColumns(UIlistOfObstacles);

	buttonObstacleAdd = new wxButton(this, 201, "Add", wxPoint(10, 610), wxSize(70, 30));
	buttonObstacleEdit = new wxButton(this, 202, "Edit", wxPoint(85, 610), wxSize(70, 30));
	buttonObstacleDelete = new wxButton(this, 203, "Delete", wxPoint(160, 610), wxSize(70, 30));
	buttonObstacleDeleteAll = new wxButton(this, 204, "Delete All", wxPoint(235, 610), wxSize(70, 30));

	labelReceivers = new wxStaticText(this, wxID_ANY, "Receivers:", wxPoint(510, 360), wxSize(100, 20));
	UIlistOfReceivers = new wxListCtrl(this, 300, wxPoint(510, 400), wxSize(300, 200), wxLC_SINGLE_SEL + wxLC_REPORT);
	createColumns(UIlistOfReceivers);

	buttonReceiverAdd = new wxButton(this, 301, "Add", wxPoint(510, 610), wxSize(70, 30));
	buttonReceiverEdit = new wxButton(this, 302, "Edit", wxPoint(585, 610), wxSize(70, 30));
	buttonReceiverDelete = new wxButton(this, 303, "Delete", wxPoint(660, 610), wxSize(70, 30));
	buttonReceiverDeleteAll = new wxButton(this, 304, "Delete All", wxPoint(735, 610), wxSize(70, 30));

	buttonExit = new wxButton(this, 666, "Exit", wxPoint(370, 420), wxSize(130, 30));
	buttonClearSelection = new wxButton(this, 665, "Clear selection", wxPoint(370, 460), wxSize(130, 30));
	buttonLoad = new wxButton(this, 664, "Load", wxPoint(370, 500), wxSize(130, 30));
	buttonSave = new wxButton(this, 663, "Save", wxPoint(370, 540), wxSize(130, 30));

	labelWalk = new wxStaticText(this, wxID_ANY, "Walk with Active Receiver", wxPoint(350, 640), wxSize(170, 30));
	buttonGoUp = new wxButton(this, 700, "Up", wxPoint(410, 670), wxSize(50, 30));
	buttonGoLeft = new wxButton(this, 701, "Left", wxPoint(350, 710), wxSize(50, 30));
	buttonGoDown = new wxButton(this, 702, "Down", wxPoint(410, 710), wxSize(50, 30));
	buttonGoRight = new wxButton(this, 703, "Right", wxPoint(470, 710), wxSize(50, 30));

	refreshWindow();
}

SoundEngineMainWindow::~SoundEngineMainWindow()
{
	SoundEngineInitializer::close();
}

void SoundEngineMainWindow::createColumns(wxListCtrl* list)
{
	int IDwidth = 35;
	int COORDwidth = 50;
	if (list->GetId() == 100) // UIlistOfSources
	{
		list->AppendColumn("ID", wxLIST_FORMAT_CENTER, IDwidth);
		list->AppendColumn("x", wxLIST_FORMAT_CENTER, COORDwidth);
		list->AppendColumn("y", wxLIST_FORMAT_CENTER, COORDwidth);
		list->AppendColumn("Attenuation", wxLIST_FORMAT_CENTER, 90);
		list->AppendColumn("IsOccluded", wxLIST_FORMAT_CENTER, 90);
		list->AppendColumn("IsVirtualized", wxLIST_FORMAT_CENTER, 100);
		list->AppendColumn("Lwa", wxLIST_FORMAT_CENTER, 60);
		list->AppendColumn("MaxDistance", wxLIST_FORMAT_CENTER, 100);
		list->AppendColumn("IsOccludable", wxLIST_FORMAT_CENTER, 100);
		list->AppendColumn("AttenuationType", wxLIST_FORMAT_CENTER, 130);
	}
	else if (list->GetId() == 200) // UIlistOfObstacles
	{
		list->AppendColumn("ID", wxLIST_FORMAT_CENTER, IDwidth);
		list->AppendColumn("x1", wxLIST_FORMAT_CENTER, COORDwidth);
		list->AppendColumn("y1", wxLIST_FORMAT_CENTER, COORDwidth);
		list->AppendColumn("x2", wxLIST_FORMAT_CENTER, 50);
		list->AppendColumn("y2", wxLIST_FORMAT_CENTER, 50);
		list->AppendColumn("Dampening", wxLIST_FORMAT_CENTER, 100);
	}
	else if (list->GetId() == 300) // UIlistOfReceivers
	{
		list->AppendColumn("ID", wxLIST_FORMAT_CENTER, IDwidth);
		list->AppendColumn("x", wxLIST_FORMAT_CENTER, COORDwidth);
		list->AppendColumn("y", wxLIST_FORMAT_CENTER, COORDwidth);
		list->AppendColumn("IsActive", wxLIST_FORMAT_CENTER, 90);
	}
	else
	{
	// error ?
	}
}

void SoundEngineMainWindow::onColumnDrag(wxListEvent& event)
{
	//UIlistOfSources->InsertItem(0, "VETO!");
	//UIlistOfObstacles->InsertItem(0, "VETO!");
	//UIlistOfReceivers->InsertItem(0, "VETO!");
	event.Skip();
}

void SoundEngineMainWindow::refreshWindowEvent(wxActivateEvent& event)
{
	refreshWindow();
	event.Skip();
}