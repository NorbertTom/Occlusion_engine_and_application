#include "PopupMemory.h"
#include "NorMemoryPoolChunk.h"
#include "SoundAPI.h"

wxBEGIN_EVENT_TABLE(PopupMemory, wxFrame)
EVT_BUTTON(1, onClosingButtonClicked)

wxEND_EVENT_TABLE()

extern SOUND_API NorMemoryPoolChunk* sourcesMemoryPool;
extern SOUND_API NorMemoryPoolChunk* obstaclesMemoryPool;
extern SOUND_API NorMemoryPoolChunk* receiversMemoryPool;

PopupMemory::PopupMemory(wxWindow* parent)
	: wxFrame(parent, wxID_ANY, "Memory Info", wxPoint(700, 300), wxSize(250, 200))
{
	m_parentWindow = parent;
	m_parentWindow->Disable();

	std::string message = printMemoryInfo();
	popupText = new wxStaticText(this, wxID_ANY, message, wxPoint(10, 10), wxSize(250, 100));
	closingButton = new wxButton(this, 1, "Close", wxPoint(85, 110), wxSize(50, 30));
	this->Show();
}

PopupMemory::~PopupMemory()
{
	m_parentWindow->Enable();
	m_parentWindow->SetFocus();
}

void PopupMemory::onClosingButtonClicked(wxCommandEvent& event)
{
	this->Close();
	event.Skip();
}

std::string PopupMemory::printMemoryInfo()
{
	unsigned int bytesUsed[3];
	unsigned int bytesTotal[3];
	bool anyTotalEqualsZero = false;

	if (sourcesMemoryPool)
	{
		bytesUsed[0] = sourcesMemoryPool->getBytesUsed();
		bytesTotal[0] = sourcesMemoryPool->getBytesTotal();
	}
	else
	{
		bytesUsed[0] = 0;
		bytesTotal[0] = 0;
		anyTotalEqualsZero = true;
	}

	if (obstaclesMemoryPool)
	{
		bytesUsed[1] = obstaclesMemoryPool->getBytesUsed();
		bytesTotal[1] = obstaclesMemoryPool->getBytesTotal();
	}
	else
	{
		bytesUsed[1] = 0;
		bytesTotal[1] = 0;
		anyTotalEqualsZero = true;
	}

	if (receiversMemoryPool)
	{
		bytesUsed[2] = receiversMemoryPool->getBytesUsed();
		bytesTotal[2] = receiversMemoryPool->getBytesTotal();
	}
	else
	{
		bytesUsed[2] = 0;
		bytesTotal[2] = 0;
		anyTotalEqualsZero = true;
	}

	std::string message = "Total memory usage [bytes]: " + std::to_string(bytesUsed[0] + bytesUsed[1] + bytesUsed[2]) + "/" + std::to_string(bytesTotal[0] + bytesTotal[1] + bytesTotal[2]) + "\n"
		+ "Sound Sources memory usage: " + std::to_string(bytesUsed[0]) + "/" + std::to_string(bytesTotal[0]) + "\n"
		+ "Obstacles memory usage: " + std::to_string(bytesUsed[1]) + "/" + std::to_string(bytesTotal[1]) + "\n"
		+ "Receivers memory usage: " + std::to_string(bytesUsed[2]) + "/" + std::to_string(bytesTotal[2]) + "\n";
	
	if (anyTotalEqualsZero)
	{
		message = message + "Please note that not all objects use NorMemoryPool (hence some = 0)";
	}

	return message;
}