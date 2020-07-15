#pragma once
#include "wx\wx.h"

class PopupLoadSave : public wxFrame
{
public:
	PopupLoadSave(wxWindow* parent, bool shouldLoad);
	~PopupLoadSave();

	wxStaticText* enterFilename = nullptr;
	wxTextCtrl* filenameInput = nullptr;

	wxButton* buttonOk = nullptr;
	wxButton* buttonCancel = nullptr;

	void onButtonOkClicked(wxCommandEvent& event);
	void onButtonCancelClicked(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

private:
	wxWindow* m_parentWindow = nullptr;
	bool m_shouldLoad = true;
};

