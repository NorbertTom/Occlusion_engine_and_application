#include "PopupObstacle.h"
#include "Obstacle.h"
#include "ListOfObstacles.h"
#include "UIDisplayHelper.h"
#include "PopupWindowSmall.h"

wxBEGIN_EVENT_TABLE(PopupObstacle, wxFrame)
	EVT_BUTTON(10, onButtonOkClicked)
	EVT_BUTTON(11, onButtonCancelClicked)
wxEND_EVENT_TABLE()

PopupObstacle::PopupObstacle(wxWindow* parent, std::string mode, ObstacleDetails obstacleDetails)
	: wxFrame(parent, wxID_ANY, mode + " obstacle", wxPoint(350, 300), wxSize(800,170))
{
	m_parentWindow = parent;
	m_windowMode = mode;
	m_obstacle = obstacleDetails.obstacle;
	m_parentWindow->Disable();

	coordPointX1 = new wxStaticText(this, wxID_ANY, "x1 [m]:", wxPoint(10, 15), wxSize(60, 20));
	coordPointY1 = new wxStaticText(this, wxID_ANY, "y1 [m]:", wxPoint(130, 15), wxSize(60, 20));
	coordPointX2 = new wxStaticText(this, wxID_ANY, "x2 [m]:", wxPoint(260, 15), wxSize(60, 20));
	coordPointY2 = new wxStaticText(this, wxID_ANY, "y2 [m]:", wxPoint(390, 15), wxSize(60, 20));
	dampening = new wxStaticText(this, wxID_ANY, "dampening [dB]:", wxPoint(520, 15), wxSize(120, 20));

	coordPointX1Input = new wxTextCtrl(this, 1, wxEmptyString, wxPoint(60,10), wxSize(60,30));
	coordPointY1Input = new wxTextCtrl(this, 2, wxEmptyString, wxPoint(190,10), wxSize(60,30));
	coordPointX2Input = new wxTextCtrl(this, 3, wxEmptyString, wxPoint(320,10), wxSize(60,30));
	coordPointY2Input = new wxTextCtrl(this, 4, wxEmptyString, wxPoint(450,10), wxSize(60,30));
	dampeningInput = new wxTextCtrl(this, 5, wxEmptyString, wxPoint(640, 10), wxSize(80, 30));

	std::string okButtonLabel = mode == "Add" ? "Add" : "Ok";
	buttonOk = new wxButton(this, 10, okButtonLabel, wxPoint(300, 70), wxSize(70, 35));
	buttonCancel = new wxButton(this, 11, "Cancel", wxPoint(400, 70), wxSize(70, 35));

	if (!obstacleDetails.isEmpty)
	{
		fillWithObstacleDetails(obstacleDetails);
	}	
}

PopupObstacle::PopupObstacle(wxWindow* parent, std::string mode)
	: PopupObstacle(parent, mode, ObstacleDetails())
{}

PopupObstacle::~PopupObstacle()
{
	m_parentWindow->Enable();
	m_parentWindow->SetFocus();
}

void PopupObstacle::onButtonOkClicked(wxCommandEvent& event)
{
	float newValues[5];
	std::string input[5];
	input[0] = static_cast<std::string>(coordPointX1Input->GetLineText(0));
	input[1] = static_cast<std::string>(coordPointY1Input->GetLineText(0));
	input[2] = static_cast<std::string>(coordPointX2Input->GetLineText(0));
	input[3] = static_cast<std::string>(coordPointY2Input->GetLineText(0));
	input[4] = static_cast<std::string>(dampeningInput->GetLineText(0));

	bool allInputsValid = true;
	for (int i = 0; i < 5; i++)
	{
		if (UIDisplayHelper::convertStringToValidNumber(input[i]))
		{
			newValues[i] = std::stof(input[i]);
		}
		else
		{
			i = 5;
			allInputsValid = false;
		}
	}

	if (allInputsValid && newValues[4] < 0)
	{
		allInputsValid = false;
		PopupWindowSmall* errorWindow = new PopupWindowSmall(this, "Error!", "Dampening cannot be less than 0");
		event.Skip();
		return;
	}

	if (allInputsValid)
	{
		if (m_windowMode == "Add")
		{
			ObstacleDescriptor newObstacleDetails(newValues[0], newValues[1], newValues[2], newValues[3], newValues[4], newValues[5]);
			listOfObstaclesPtr->addObstacle(newObstacleDetails);
		}
		else if (m_windowMode == "Edit")
		{
			m_obstacle->setPosX1(newValues[0]);
			m_obstacle->setPosY1(newValues[1]);
			m_obstacle->setPosX2(newValues[2]);
			m_obstacle->setPosY2(newValues[3]);
			m_obstacle->setDampening(newValues[4]);
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

void PopupObstacle::onButtonCancelClicked(wxCommandEvent& event)
{
	this->Close();
}

void PopupObstacle::fillWithObstacleDetails(ObstacleDetails& obstacleDetails)
{
	coordPointX1Input->WriteText(UIDisplayHelper::toString(obstacleDetails.x1));
	coordPointY1Input->WriteText(UIDisplayHelper::toString(obstacleDetails.y1));
	coordPointX2Input->WriteText(UIDisplayHelper::toString(obstacleDetails.x2));
	coordPointY2Input->WriteText(UIDisplayHelper::toString(obstacleDetails.y2));
	dampeningInput->WriteText(UIDisplayHelper::toString(obstacleDetails.dampening));
}