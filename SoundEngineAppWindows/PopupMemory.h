#pragma once

#include "wx\wx.h"
#include <string>

class PopupMemory : public wxFrame
{
public:
	PopupMemory(wxWindow* parent);
	~PopupMemory();

	wxWindow* m_parentWindow = nullptr;
	wxStaticText* popupText = nullptr;
	wxButton* closingButton = nullptr;

	void onClosingButtonClicked(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

private:
	std::string printMemoryInfo();

};

