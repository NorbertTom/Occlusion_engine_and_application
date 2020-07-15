#pragma once
#include "wx\wx.h"
#include <string>

class SoundSource;
enum class AttenuationType;

struct SourceDetails
{
	SoundSource* m_source = nullptr;
	float m_x, m_y, m_Lwa, m_maxDistance;
	bool m_isOccludable;
	AttenuationType m_attenuationType;
	bool m_isEmpty = true;

	SourceDetails(SoundSource* SOURCE, float X, float Y, float LWA, float MaxDISTANCE, bool IsOccludable,
		AttenuationType AttenuationTYPE)
		: m_source(SOURCE), m_x(X), m_y(Y), m_Lwa(LWA), m_maxDistance(MaxDISTANCE), m_isOccludable(IsOccludable),
		m_attenuationType(AttenuationTYPE), m_isEmpty(false) {};

	SourceDetails() {};

};

class PopupSource : public wxFrame
{
public:
	PopupSource(wxWindow* parent, std::string mode, SourceDetails sourceDetails);
	PopupSource(wxWindow* parent, std::string mode);
	~PopupSource();


	wxStaticText* txtPosX = nullptr;
	wxStaticText* txtPosY = nullptr;
	wxStaticText* txtLwa = nullptr; // <----- pick up from there
	wxStaticText* txtMaxDistance = nullptr;
	wxStaticText* txtIsOccludable = nullptr;
	wxStaticText* txtAttenuationType = nullptr;

	wxTextCtrl* posXInput = nullptr;
	wxTextCtrl* posYInput = nullptr;
	wxTextCtrl* LwaInput = nullptr;
	wxTextCtrl* maxDistanceInput = nullptr;
	wxChoice* isOccludableInput = nullptr;
	wxChoice* attenuationTypeInput = nullptr;

	wxButton* buttonOk = nullptr;
	wxButton* buttonCancel = nullptr;

	void onButtonOkClicked(wxCommandEvent& event);
	void onButtonCancelClicked(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

	void fillWithSourceDetails(SourceDetails& receiverDetails);

private:
	wxWindow* m_parentWindow = nullptr;
	std::string m_windowMode;
	SoundSource* m_source;
};