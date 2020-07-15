#pragma once
#include "wx\wx.h"
#include <string>

class PopupWindowSmall : public wxFrame
{
public:
	PopupWindowSmall(wxWindow* parent, std::string title, std::string message);
	~PopupWindowSmall();

	wxWindow* m_parentWindow = nullptr;
	wxWindow* m_parentOfParentWindow = nullptr;
	wxStaticText* popupText = nullptr;
	wxButton* closingButton = nullptr;

	void onClosingButtonClicked(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

