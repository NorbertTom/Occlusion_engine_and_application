#include "PopupWindowSmall.h"

wxBEGIN_EVENT_TABLE(PopupWindowSmall, wxFrame)
	EVT_BUTTON(1, onClosingButtonClicked)

wxEND_EVENT_TABLE()

PopupWindowSmall::PopupWindowSmall(wxWindow* parent, std::string title, std::string message) 
	: wxFrame(parent, wxID_ANY, title, wxPoint(500, 350), wxSize(430,120))
{
	m_parentWindow = parent;
	m_parentWindow->Disable();
	popupText = new wxStaticText(this, wxID_ANY, message, wxPoint(10, 10), wxSize(400, 20), wxTE_CENTRE);
	closingButton = new wxButton(this, 1, "OK", wxPoint(190, 40), wxSize(50, 30));
	this->Show();
}

PopupWindowSmall::~PopupWindowSmall()
{
	m_parentWindow->Enable();
	m_parentWindow->SetFocus();
}

void PopupWindowSmall::onClosingButtonClicked(wxCommandEvent& event)
{
	this->Close();
	event.Skip();
}