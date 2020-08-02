#pragma once
#include "wx\wx.h"
#include "wx\listctrl.h"

enum class AttenuationType;
enum class MoveReceiverDirection;

class SoundEngineMainWindow : public wxFrame
{

public:
	SoundEngineMainWindow();
	~SoundEngineMainWindow();

	wxTextCtrl* textWindow = nullptr;
	wxStaticText* labelSources = nullptr;
	wxListCtrl* UIlistOfSources = nullptr;
	wxStaticText* labelObstacles = nullptr;
	wxListCtrl* UIlistOfObstacles = nullptr;
	wxStaticText* labelReceivers = nullptr;
	wxListCtrl* UIlistOfReceivers = nullptr;

	wxButton* buttonExit = nullptr;
	wxButton* buttonClearSelection = nullptr;
	wxButton* buttonLoad = nullptr;
	wxButton* buttonSave = nullptr;
	wxButton* buttonMemory = nullptr;

	wxStaticText* labelWalk = nullptr;
	wxButton* buttonGoUp = nullptr;
	wxButton* buttonGoLeft = nullptr;
	wxButton* buttonGoDown = nullptr;
	wxButton* buttonGoRight = nullptr;


	wxButton* buttonSourceAdd = nullptr;
	wxButton* buttonSourceEdit = nullptr;
	wxButton* buttonSourceDelete = nullptr;
	wxButton* buttonSourceDeleteAll = nullptr;

	wxButton* buttonObstacleAdd = nullptr;
	wxButton* buttonObstacleEdit = nullptr;
	wxButton* buttonObstacleDelete = nullptr;
	wxButton* buttonObstacleDeleteAll = nullptr;

	wxButton* buttonReceiverAdd = nullptr;
	wxButton* buttonReceiverEdit = nullptr;
	wxButton* buttonReceiverDelete = nullptr;
	wxButton* buttonReceiverDeleteAll = nullptr;

	void onButtonClickedExit(wxCommandEvent& event);
	void onButtonClickedClearSelection(wxCommandEvent& event);
	void onButtonClickedLoad(wxCommandEvent& event);
	void onButtonClickedSave(wxCommandEvent& event);
	void onButtonClickedMemory(wxCommandEvent& event);

	void onButtonClickedSourceAdd(wxCommandEvent& event);
	void onButtonClickedSourceEdit(wxCommandEvent& event);
	void onButtonClickedSourceDelete(wxCommandEvent& event);
	void onButtonClickedSourceDeleteAll(wxCommandEvent& event);

	void onButtonClickedObstacleAdd(wxCommandEvent& event);
	void onButtonClickedObstacleEdit(wxCommandEvent& event);
	void onButtonClickedObstacleDelete(wxCommandEvent& event);
	void onButtonClickedObstacleDeleteAll(wxCommandEvent& event);
		 
	void onButtonClickedGoUp(wxCommandEvent& event);
	void onButtonClickedGoLeft(wxCommandEvent& event);
	void onButtonClickedGoDown(wxCommandEvent& event);
	void onButtonClickedGoRight(wxCommandEvent& event);

	void onButtonClickedReceiverAdd(wxCommandEvent& event);
	void onButtonClickedReceiverEdit(wxCommandEvent& event);
	void onButtonClickedReceiverDelete(wxCommandEvent& event);
	void onButtonClickedReceiverDeleteAll(wxCommandEvent& event);

	void onUIlistOfSourcesSelect(wxListEvent& event);
	void onUIlistOfSourcesDclick(wxListEvent& event);
	void onUIlistOfSourcesDeselect(wxListEvent& event);
	void onUIlistOfObstaclesSelect(wxListEvent& event);
	void onUIlistOfObstaclesDclick(wxListEvent& event);
	void onUIlistOfObstaclesDeselect(wxListEvent& event);
	void onUIlistOfReceiversSelect(wxListEvent& event);
	void onUIlistOfReceiversDclick(wxListEvent& event);
	void onUIlistOfReceiversDeselect(wxListEvent& event);

	void onColumnDrag(wxListEvent& event);
	wxDECLARE_EVENT_TABLE();

	void createColumns(wxListCtrl* list);
	void resetButtonsState();
	void refreshWindowEvent(wxActivateEvent& event);
	void refreshWindow();
	void fillTablesWithObjects();
	void clearTables();

private:
	std::string attenuationToString(AttenuationType attenuationType);
};