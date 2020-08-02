#pragma once
#include "wx\wx.h"
#include <string>

class Obstacle;

struct ObstacleDetails
{
	Obstacle* obstacle = nullptr;
	float x1, y1, x2, y2, dampening;
	bool isEmpty = true;

	ObstacleDetails(Obstacle* OBSTACLE, float X1, float Y1, float X2, float Y2, float DAMPENING)
		: obstacle(OBSTACLE), x1(X1), y1(Y1), x2(X2), y2(Y2), dampening(DAMPENING), isEmpty(false) {};

	ObstacleDetails() {};

};

class PopupObstacle : public wxFrame
{
public:
	PopupObstacle(wxWindow* parent, std::string mode, ObstacleDetails obstacleDetails);
	PopupObstacle(wxWindow* parent, std::string mode);
	~PopupObstacle();


	wxStaticText* coordPointX1 = nullptr;
	wxStaticText* coordPointY1 = nullptr;
	wxStaticText* coordPointX2 = nullptr;
	wxStaticText* coordPointY2 = nullptr;
	wxStaticText* dampening = nullptr;
	
	wxStaticText* txtCountStatus = nullptr;

	wxTextCtrl* coordPointX1Input = nullptr;
	wxTextCtrl* coordPointY1Input = nullptr;
	wxTextCtrl* coordPointX2Input = nullptr;
	wxTextCtrl* coordPointY2Input = nullptr;
	wxTextCtrl* dampeningInput = nullptr;

	wxButton* buttonOk = nullptr;
	wxButton* buttonCancel = nullptr;

	void onButtonOkClicked(wxCommandEvent& event);
	void onButtonCancelClicked(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

	void fillWithObstacleDetails(ObstacleDetails& obstacleDetails);

private:
	wxWindow* m_parentWindow = nullptr;
	std::string m_windowMode;
	Obstacle* m_obstacle;
	bool m_shouldFocusOnMainWindow = true;
};

