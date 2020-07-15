#include "PopupLoadSave.h"
#include "SoundAPI.h"

#include <string>

#include "UIDisplayHelper.h"
#include "PopupWindowSmall.h"
#include "LoadingData.h"
#include "SavingData.h"

wxBEGIN_EVENT_TABLE(PopupLoadSave, wxFrame)
	EVT_BUTTON(10, onButtonOkClicked)
	EVT_BUTTON(11, onButtonCancelClicked)
wxEND_EVENT_TABLE()


PopupLoadSave::PopupLoadSave(wxWindow* parent, bool ShouldLoad)
	: wxFrame(parent, wxID_ANY, "Enter filename", wxPoint(350, 300), wxSize(370, 160)),
	m_parentWindow(parent), m_shouldLoad(ShouldLoad)
{
	m_parentWindow->Disable();
	this->Show();

	enterFilename = new wxStaticText(this, wxID_ANY, "Enter filename: ", wxPoint(10, 15), wxSize(160, 20));
	filenameInput = new wxTextCtrl(this, 1, wxEmptyString, wxPoint(160, 10), wxSize(150, 30));

	if (m_shouldLoad)
	{
		buttonOk = new wxButton(this, 10, "Load", wxPoint(110, 70), wxSize(70, 35));
	}
	else
	{
		buttonOk = new wxButton(this, 10, "Save", wxPoint(110, 70), wxSize(70, 35));
	}
	buttonCancel = new wxButton(this, 11, "Cancel", wxPoint(210, 70), wxSize(70, 35));
}


PopupLoadSave::~PopupLoadSave()
{
	m_parentWindow->Enable();
	m_parentWindow->SetFocus();
}

void PopupLoadSave::onButtonOkClicked(wxCommandEvent& event)
{
	std::string filename;
	filename = static_cast<std::string>(filenameInput->GetLineText(0));
	if (UIDisplayHelper::isValidString(filename))
	{
		if (m_shouldLoad)
		{
			if (loadingData->loadDataFromFile(filename))
			{
				this->Close();
			}
			else
			{
				PopupWindowSmall* popupWindow = new PopupWindowSmall(this, "Error", "No file found");
			}
		}
		else
		{
			savingData->saveAll(filename);
			this->Close();
		}
	}
	else
	{
		PopupWindowSmall* popupWindow = new PopupWindowSmall(this, "Invalid filename", "Please use only characters and numbers");
	}
	event.Skip();
}

void PopupLoadSave::onButtonCancelClicked(wxCommandEvent& event)
{
	this->Close();
	event.Skip();
}