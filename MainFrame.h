#pragma once
#include <wx/wx.h>
#include <string>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	wxChoice* gameRegionChoice;
	wxChoice* categoryChoice;
	wxTextCtrl* layoutFilePathBox;

	void OnStartButtonClicked(wxCommandEvent& evt);
	void OnLayoutBrowseButtonClicked(wxCommandEvent& evt);
	bool ConfigureAutosplitter(int gameRegion, int category, std::string& layoutFilePath);
};

