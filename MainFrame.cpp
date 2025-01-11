#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/filectrl.h>

enum ids
{
	GAME_REGION_CHOICE = 2,
	CATEGORY_CHOICE = 3,
	LAYOUT_BROWSE = 4,
	LAYOUT_TEXT_BOX = 5,
	START_BUTTON = 6
};

enum class Region
{
	USA = 0,
	PAL = 1
};

enum class Category
{
	SPEEDSTER = 0,
	WORLD_SERIES = 1
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(START_BUTTON, MainFrame::OnStartButtonClicked)
EVT_BUTTON(LAYOUT_BROWSE, MainFrame::OnLayoutBrowseButtonClicked)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* panel = new wxPanel(this);

	/* Unneeded but needed if I decide to implement auto-downloading LiveSplit.DeSmuME.dll
	// choice between fresh setup or just changing autosplitter
	wxArrayString setupArray = { "First-time setup", "Only change autosplit config" };
	wxRadioBox* setupChoice = new wxRadioBox(panel, wxID_ANY, "Setup choice", wxPoint(50, 10), wxSize(-1, -1), setupArray);
	*/

	// select game region!
	wxStaticText* selectGameRegionText = new wxStaticText(panel, wxID_ANY, "Select Game Region:", wxPoint(50, 50));
	wxArrayString regionArray = { "USA", "PAL" };
	gameRegionChoice = new wxChoice(panel, GAME_REGION_CHOICE, wxPoint(550, 47), wxSize(50, -1), regionArray);

	// select category!
	wxStaticText* selectCategoryText = new wxStaticText(panel, wxID_ANY, "Select Speedrun Category:", wxPoint(50, 100));
	wxArrayString categoryArray = { "Speedster%", "World Series%" };
	categoryChoice = new wxChoice(panel, CATEGORY_CHOICE, wxPoint(490, 97), wxSize(110, -1), categoryArray);

	/* Unneeded, maybe in the future auto-download LiveSplit.DeSmuME.dll and place it in the Components directory
	// select livesplit directory!
	wxStaticText* selectLiveSplitDirectoryText = new wxStaticText(panel, wxID_ANY, "Select LiveSplit Directory:", wxPoint(50, 150));
	wxButton* livesplitBrowseButton = new wxButton(panel, wxID_ANY, "...", wxPoint(250, 145), wxSize(30, 30));
	wxTextCtrl* livesplitDirectoryBox = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(300, 149), wxSize(300, -1));
	*/

	// select livesplit layout!
	wxStaticText* selectLayoutText = new wxStaticText(panel, wxID_ANY, "Select LiveSplit Layout:", wxPoint(50, 150));
	wxButton* layoutBrowseButton = new wxButton(panel, LAYOUT_BROWSE, "...", wxPoint(250, 145), wxSize(30, 30));
	layoutFilePathBox = new wxTextCtrl(panel, LAYOUT_TEXT_BOX, wxEmptyString, wxPoint(300, 149), wxSize(300, -1));
	layoutFilePathBox->SetEditable(false); // only editable from selecting file

	// start the configuration process!!!
	wxButton* startButton = new wxButton(panel, START_BUTTON, "Start!", wxPoint(280, 230), wxSize(100, 35));

	CreateStatusBar();
}

void MainFrame::OnStartButtonClicked(wxCommandEvent& evt)
{
	// error checking
	if (gameRegionChoice->GetCurrentSelection() == -1 || categoryChoice->GetCurrentSelection() == -1 || layoutFilePathBox->IsEmpty())
	{
		wxLogStatus("Selections not complete!");
	}

	else
	{
		wxLogStatus("Starting...");

		wxString layoutFilePath = layoutFilePathBox->GetValue();
		if (ConfigureAutosplitter(gameRegionChoice->GetCurrentSelection(), categoryChoice->GetCurrentSelection(), layoutFilePath) == true)
		{
			wxLogStatus("Configured successfully! Make sure to use DeSmuME 0.9.11 and set your start time to 0.20s!");
		}
		else
		{
			// this should hopefully only trigger if it's the user's fault (corrupt layout, etc.)
			wxLogStatus("Configuration failed!");
		}
	}
}

void MainFrame::OnLayoutBrowseButtonClicked(wxCommandEvent& evt)
{
	// Create a file dialog with a "File Open" style
	wxFileDialog openFileDialog(this, "Open File", "", "", "*.lsl", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	// "", "", "*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST

	// If the user selects a file
	if (openFileDialog.ShowModal() == wxID_OK)
	{
		// set text box to file path
		wxString filePath = openFileDialog.GetPath();
		layoutFilePathBox->SetValue(filePath);
	}
}

// returns true if the configuration was successful
bool MainFrame::ConfigureAutosplitter(int gameRegion, int category, wxString& layoutFilePath)
{
	return true;
}