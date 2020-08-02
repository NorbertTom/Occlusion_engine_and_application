#pragma once
#include "wx\wx.h"
#include <string>

class Receiver;

struct ReceiverDetails
{
	Receiver* m_receiver = nullptr;
	float m_x, m_y;
	bool m_isActive;
	bool m_isEmpty = true;

	ReceiverDetails(Receiver* RECEIVER, float X, float Y, bool IsACTIVE)
		: m_receiver(RECEIVER), m_x(X), m_y(Y), m_isActive(IsACTIVE), m_isEmpty(false) {};

	ReceiverDetails() {};

};

class PopupReceiver : public wxFrame
{
public:
	PopupReceiver(wxWindow* parent, std::string mode, ReceiverDetails receiverDetails);
	PopupReceiver(wxWindow* parent, std::string mode);
	~PopupReceiver();


	wxStaticText* coordPointXtxt = nullptr;
	wxStaticText* coordPointYtxt = nullptr;
	wxStaticText* isActivetxt = nullptr;

	wxStaticText* txtCountStatus = nullptr;

	wxTextCtrl* coordPointXInput = nullptr;
	wxTextCtrl* coordPointYInput = nullptr;
	wxChoice* isActiveInput = nullptr;

	wxButton* buttonOk = nullptr;
	wxButton* buttonCancel = nullptr;

	void onButtonOkClicked(wxCommandEvent& event);
	void onButtonCancelClicked(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

	void fillWithReceiverDetails(ReceiverDetails& receiverDetails);

private:
	wxWindow* m_parentWindow = nullptr;
	std::string m_windowMode;
	Receiver* m_receiver;

	bool m_focusOnMain = true;
};

