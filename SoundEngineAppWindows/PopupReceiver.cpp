#include "PopupReceiver.h"
#include "UIDisplayHelper.h"
#include "Receiver.h"
#include "ListOfReceivers.h"
#include "PopupWindowSmall.h"

wxBEGIN_EVENT_TABLE(PopupReceiver, wxFrame)
	EVT_BUTTON(10, onButtonOkClicked)
	EVT_BUTTON(11, onButtonCancelClicked)
wxEND_EVENT_TABLE()


PopupReceiver::PopupReceiver(wxWindow* parent, std::string mode, ReceiverDetails receiverDetails)
	: wxFrame(parent, wxID_ANY, mode + " receiver", wxPoint(350, 300), wxSize(500, 170))
{
	m_parentWindow = parent;
	m_windowMode = mode;
	m_receiver = receiverDetails.m_receiver;
	m_parentWindow->Disable();

	coordPointXtxt = new wxStaticText(this, wxID_ANY, "x [m]:", wxPoint(10, 15), wxSize(60, 20));
	coordPointYtxt = new wxStaticText(this, wxID_ANY, "y [m]:", wxPoint(130, 15), wxSize(60, 20));
	isActivetxt = new wxStaticText(this, wxID_ANY, "isActive:", wxPoint(260, 15), wxSize(60, 20));

	std::string countText = "Receivers status = " + std::to_string(listOfReceiversPtr->getReceiversAmount()) + " / " + std::to_string(listOfReceiversPtr->getReceiversAmountLimit());
	txtCountStatus = new wxStaticText(this, wxID_ANY, countText, wxPoint(10, 70), wxSize(130, 20));

	coordPointXInput = new wxTextCtrl(this, 1, wxEmptyString, wxPoint(60, 10), wxSize(60, 30));
	coordPointYInput = new wxTextCtrl(this, 2, wxEmptyString, wxPoint(190, 10), wxSize(60, 30));
	wxArrayString choice;
	if (mode == "Edit" && receiverDetails.m_isActive == true)
	{
		choice.Add("true");
	}
	else
	{
		choice.Add("true");
		choice.Add("false");
	}
	isActiveInput = new wxChoice(this, 3, wxPoint(320, 10), wxSize(80, 30), choice);
	isActiveInput->SetSelection(0);

	std::string okButtonLabel = mode == "Add" ? "Add" : "Ok";
	buttonOk = new wxButton(this, 10, okButtonLabel, wxPoint(150, 70), wxSize(70, 35));
	buttonCancel = new wxButton(this, 11, "Cancel", wxPoint(250, 70), wxSize(70, 35));

	if (!receiverDetails.m_isEmpty)
	{
		fillWithReceiverDetails(receiverDetails);
	}
	this->Show();
}

PopupReceiver::PopupReceiver(wxWindow* parent, std::string mode)
	: PopupReceiver(parent, mode, ReceiverDetails())
{
	if (listOfReceiversPtr->getReceiversAmount() == listOfReceiversPtr->getReceiversAmountLimit() && mode == "Add")
	{
		m_focusOnMain = false;
		this->Close();
		PopupWindowSmall* errorWindow = new PopupWindowSmall(parent, "Error!", "Cannot add any more receivers, memory full");
	}
}

PopupReceiver::~PopupReceiver()
{
	if (m_focusOnMain)
	{
		m_parentWindow->Enable();
		m_parentWindow->SetFocus();
	}
	else
	{
		//PopupWindowSmall will take care of that
	}
}

void PopupReceiver::onButtonOkClicked(wxCommandEvent& event)
{
	std::string input[2];
	int activeChoice = 0;
	float newValues[2];

	input[0] = static_cast<std::string>(coordPointXInput->GetLineText(0));
	input[1] = static_cast<std::string>(coordPointYInput->GetLineText(0));
	activeChoice = isActiveInput->GetSelection();
	bool allInputsValid = true;
	for (int i = 0; i < 2; i++)
	{
		if (UIDisplayHelper::convertStringToValidNumber(input[i]))
		{
			newValues[i] = std::stof(input[i]);
		}
		else
		{
			i = 2;
			allInputsValid = false;
		}
	}

	if (allInputsValid)
	{
		if (m_windowMode == "Add")
		{
			int idToActivate;
			bool isFirstReceiver = listOfReceiversPtr->getReceiversAmount() == 0 ? true : false;

			if (!isFirstReceiver)
			{
				idToActivate = listOfReceiversPtr->getActive()->getId();
			}

			Receiver* newReceiver = listOfReceiversPtr->createReceiver(newValues[0], newValues[1]);

			if (activeChoice == 0)
			{
				idToActivate = newReceiver->getId();
			}
			else if (isFirstReceiver)
			{
				PopupWindowSmall* errorWindow = new PopupWindowSmall(m_parentWindow, "Info", "At least one receiver has to be active");
				idToActivate = newReceiver->getId();
				m_focusOnMain = false;
			}
			else
			{}
			listOfReceiversPtr->activateById(idToActivate);
		}
		else if (m_windowMode == "Edit")
		{
			m_receiver->setPosX(newValues[0]);
			m_receiver->setPosY(newValues[1]);
			if (activeChoice == 0)
			{
				int id = m_receiver->getId();
				listOfReceiversPtr->activateById(id);
			}
			else
			{ }
		}
		else
		{
			//Shouldn't happen
			int* a = nullptr;
			delete a;
		}
		this->Close();
	}
	else
	{
		PopupWindowSmall* errorWindow = new PopupWindowSmall(this, "Error!", "Some numbers are not a valid floats");
	}
	event.Skip();
}

void PopupReceiver::onButtonCancelClicked(wxCommandEvent& event)
{
	this->Close();
}


void PopupReceiver::fillWithReceiverDetails(ReceiverDetails& receiverDetails)
{
	coordPointXInput->WriteText(UIDisplayHelper::toString(receiverDetails.m_x));
	coordPointYInput->WriteText(UIDisplayHelper::toString(receiverDetails.m_y));
	int option = 0;
	if (receiverDetails.m_isActive)
	{}
	else
	{
		option = 1;
	}
	isActiveInput->SetSelection(option);
}