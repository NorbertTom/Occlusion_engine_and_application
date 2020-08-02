#include "PopupSource.h"
#include "SoundSource.h"
#include "ListOfSources.h"
#include "UIDisplayHelper.h"
#include "PopupWindowSmall.h"

wxBEGIN_EVENT_TABLE(PopupSource, wxFrame)
EVT_BUTTON(10, onButtonOkClicked)
EVT_BUTTON(11, onButtonCancelClicked)
wxEND_EVENT_TABLE()


PopupSource::PopupSource(wxWindow* parent, std::string mode, SourceDetails sourceDetails)
	: wxFrame(parent, wxID_ANY, mode + " source", wxPoint(350, 300), wxSize(1080, 170))
{
	m_parentWindow = parent;
	m_windowMode = mode;
	m_source = sourceDetails.m_source;
	m_parentWindow->Disable();

	txtPosX = new wxStaticText(this, wxID_ANY, "x [m]:", wxPoint(10, 15), wxSize(60, 20));
	txtPosY = new wxStaticText(this, wxID_ANY, "y [m]:", wxPoint(130, 15), wxSize(60, 20));
	txtLwa = new wxStaticText(this, wxID_ANY, "Lwa [dB A]:", wxPoint(260, 15), wxSize(80, 20));
	txtMaxDistance = new wxStaticText(this, wxID_ANY, "maxDistance [m]:", wxPoint(410, 15), wxSize(130, 20));
	txtIsOccludable = new wxStaticText(this, wxID_ANY, "isOccludable:", wxPoint(600, 15), wxSize(90, 20));
	txtAttenuationType = new wxStaticText(this, wxID_ANY, "AttenuationType:", wxPoint(760, 15), wxSize(120, 20));
	
	std::string countText = "Sources status = " + std::to_string(listOfSourcesPtr->getSourcesAmount()) + " / " + std::to_string(listOfSourcesPtr->getSourcesAmountLimit());
	txtCountStatus = new wxStaticText(this, wxID_ANY, countText, wxPoint(10, 70), wxSize(130, 20));
	
	posXInput = new wxTextCtrl(this, 1, wxEmptyString, wxPoint(60, 10), wxSize(60, 30));
	posYInput = new wxTextCtrl(this, 2, wxEmptyString, wxPoint(180, 10), wxSize(60, 30));
	LwaInput = new wxTextCtrl(this, 3, wxEmptyString, wxPoint(340, 10), wxSize(60, 30));
	maxDistanceInput = new wxTextCtrl(this, 4, wxEmptyString, wxPoint(530, 10), wxSize(60, 30));

	wxArrayString choiceIsOccludable;
	choiceIsOccludable.Add("true");
	choiceIsOccludable.Add("false");
	isOccludableInput = new wxChoice(this, 5, wxPoint(690, 10), wxSize(60, 30), choiceIsOccludable);
	isOccludableInput->SetSelection(0);

	wxArrayString choiceAttenuationType;
	choiceAttenuationType.Add("PointSource");
	choiceAttenuationType.Add("LineSource");
	choiceAttenuationType.Add("NoAttenuation");
	attenuationTypeInput = new wxChoice(this, 6, wxPoint(880, 10), wxSize(130, 30), choiceAttenuationType);
	attenuationTypeInput->SetSelection(0);

	std::string okButtonLabel = mode == "Add" ? "Add" : "Ok";
	buttonOk = new wxButton(this, 10, okButtonLabel, wxPoint(410, 70), wxSize(70, 35));
	buttonCancel = new wxButton(this, 11, "Cancel", wxPoint(510, 70), wxSize(70, 35));

	if (!sourceDetails.m_isEmpty)
	{
		fillWithSourceDetails(sourceDetails);
	}
	this->Show();
}

PopupSource::PopupSource(wxWindow* parent, std::string mode)
	: PopupSource(parent, mode, SourceDetails())
{
	if (listOfSourcesPtr->getSourcesAmount() == listOfSourcesPtr->getSourcesAmountLimit() && mode == "Add")
	{
		m_shouldAutomaticallyFocusOnParentWindow = false;
		this->Close();
		PopupWindowSmall* errorWindow = new PopupWindowSmall(parent, "Error!", "Cannot add any more sources, memory full");
	}
}


PopupSource::~PopupSource()
{
	if (m_shouldAutomaticallyFocusOnParentWindow)
	{
		m_parentWindow->Enable();
		m_parentWindow->SetFocus();
	}
}

void PopupSource::onButtonOkClicked(wxCommandEvent& event)
{
	float newValues[4];
	std::string input[4];
	input[0] = static_cast<std::string>(posXInput->GetLineText(0));
	input[1] = static_cast<std::string>(posYInput->GetLineText(0));
	input[2] = static_cast<std::string>(LwaInput->GetLineText(0));
	input[3] = static_cast<std::string>(maxDistanceInput->GetLineText(0));

	bool allInputsValid = true;
	for (int i = 0; i < 4; i++)
	{
		if (UIDisplayHelper::convertStringToValidNumber(input[i]))
		{
			newValues[i] = std::stof(input[i]);
		}
		else
		{
			i = 4;
			allInputsValid = false;
		}
	}
	bool isOccludableChoice = isOccludableInput->GetSelection() == 0 ? true : false;
	int attenuationChoice = attenuationTypeInput->GetSelection();

	if (allInputsValid && newValues[2] <= 0)
	{
		allInputsValid = false;
		PopupWindowSmall* errorWindow = new PopupWindowSmall(this, "Error!", "Lwa cannot be less or equal to 0");
		event.Skip();
		return;
	}
	if (allInputsValid && newValues[3] <= 0)
	{
		allInputsValid = false;
		PopupWindowSmall* errorWindow = new PopupWindowSmall(this, "Error!", "MaxDistance cannot be less or equal to 0");
		event.Skip();
		return;
	}

	if (allInputsValid)
	{
		if (m_windowMode == "Add")
		{
			SoundSourceDescriptor newSourceDetails(newValues[0], newValues[1], newValues[2], newValues[3], isOccludableChoice, 
				static_cast<AttenuationType>(attenuationChoice));
			listOfSourcesPtr->addSource(newSourceDetails);
		}
		else if (m_windowMode == "Edit")
		{
			m_source->setPosX(newValues[0]);
			m_source->setPosY(newValues[1]);
			m_source->setLwa(newValues[2]);
			m_source->setMaxDistance(newValues[3]);
			m_source->setIsOccludable(isOccludableChoice);
			m_source->setAttenuationCurve(static_cast<AttenuationType>(attenuationChoice));
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

void PopupSource::onButtonCancelClicked(wxCommandEvent& event)
{
	this->Close();
}

void PopupSource::fillWithSourceDetails(SourceDetails& sourceDetails)
{
	posXInput->WriteText(UIDisplayHelper::toString(sourceDetails.m_x));
	posYInput->WriteText(UIDisplayHelper::toString(sourceDetails.m_y));
	LwaInput->WriteText(UIDisplayHelper::toString(sourceDetails.m_Lwa));
	maxDistanceInput->WriteText(UIDisplayHelper::toString(sourceDetails.m_maxDistance));
	
	int selection = sourceDetails.m_isOccludable ? 0 : 1;
	isOccludableInput->SetSelection(selection);

	selection = static_cast<int>(sourceDetails.m_attenuationType);
	attenuationTypeInput->SetSelection(selection);
}