#include "MainFrame.h"
#include "autosplitterConfigurations.h"
#include <wx/wx.h>
#include <wx/filectrl.h>
#include <fstream>

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

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* panel = new wxPanel(this);

	// select game region!
	wxStaticText* selectGameRegionText = new wxStaticText(panel, wxID_ANY, "Select Game Region:", wxPoint(50, 50));
	wxArrayString regionArray = { "USA", "PAL" };
	gameRegionChoice = new wxChoice(panel, wxID_ANY, wxPoint(550, 47), wxSize(50, -1), regionArray);

	// select category!
	wxStaticText* selectCategoryText = new wxStaticText(panel, wxID_ANY, "Select Speedrun Category:", wxPoint(50, 100));
	wxArrayString categoryArray = { "Speedster%", "World Series%" };
	categoryChoice = new wxChoice(panel, wxID_ANY, wxPoint(490, 97), wxSize(110, -1), categoryArray);

	// select livesplit layout!
	wxStaticText* selectLayoutText = new wxStaticText(panel, wxID_ANY, "Select LiveSplit Layout:", wxPoint(50, 150));
	wxButton* layoutBrowseButton = new wxButton(panel, wxID_ANY, "...", wxPoint(250, 145), wxSize(30, 30));
	layoutFilePathBox = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(300, 149), wxSize(300, -1));
	layoutFilePathBox->SetEditable(false); // only editable from selecting file

	// start the configuration process!!!
	wxButton* startButton = new wxButton(panel, wxID_ANY, "Start!", wxPoint(280, 230), wxSize(100, 35));

	// Binds from buttons to functions
	layoutBrowseButton->Bind(wxEVT_BUTTON, &MainFrame::OnLayoutBrowseButtonClicked, this);
	startButton->Bind(wxEVT_BUTTON, &MainFrame::OnStartButtonClicked, this);
	

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

		std::string layoutFilePath = layoutFilePathBox->GetValue().ToStdString();
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
bool MainFrame::ConfigureAutosplitter(int gameRegion, int category, std::string& layoutFilePath)
{
	std::string autosplitterConfig{};
	if (gameRegion == (int)Region::USA)
	{
		if (category == (int)Category::SPEEDSTER)
		{
			autosplitterConfig = usaSpeedster;
		}
		else // World Series
		{
			return false; // not supported yet
		}
	}

	if (gameRegion == (int)Region::PAL)
	{
		if (category == (int)Category::SPEEDSTER)
		{
			return false; // not supported yet
		}
		else // World Series
		{
			return false; // not supported yet
		}
	}

	std::ifstream layoutFile{ layoutFilePath };
	std::size_t desmumeIndex{};
	std::size_t desmumeEndIndex{};
	bool inDesmumeSettings{ false };
	std::size_t componentEndIndex{};
	std::string currLine{};
	std::vector<std::string> lines{};
	std::vector<std::string> newLayoutText{};

	while (std::getline(layoutFile, currLine)) {
		lines.push_back(currLine);
	}
	layoutFile.close();

	for (std::size_t i{ 0 }; i < lines.size(); ++i)
	{
		if (lines[i] == "      <Path>LiveSplit.DeSmuME.dll</Path>")
		{
			desmumeIndex = i;
			inDesmumeSettings = true;
		}

		else if (inDesmumeSettings && lines[i] == "      </Settings>")
		{
			desmumeEndIndex = i;
			inDesmumeSettings = false;
		}

		else if (lines[i] == "  </Components>")
		{
			componentEndIndex = i;
		}
	}

	if (desmumeIndex != 0) // if there is already an existing desmume component
	{
		for (std::size_t i{ 0 }; i <= desmumeIndex; ++i)
		{
			newLayoutText.push_back(lines[i]);
		}

		newLayoutText.push_back(autosplitterConfig);

		for (std::size_t i{ desmumeEndIndex + 1 }; i < lines.size(); ++i)
		{
			newLayoutText.push_back(lines[i]);
		}
	}

	else // fresh layout setup
	{
		for (std::size_t i{ 0 }; i < componentEndIndex; ++i)
		{
			newLayoutText.push_back(lines[i]);
		}

		newLayoutText.push_back(headerText);
		newLayoutText.push_back(autosplitterConfig);
		newLayoutText.push_back(footerText);

		for (std::size_t i{ componentEndIndex }; i < lines.size(); ++i)
		{
			newLayoutText.push_back(lines[i]);
		}
	}

	std::ofstream updatedLayout(layoutFilePath, std::ios::trunc);
	for (std::string line : newLayoutText)
	{
		 updatedLayout << line;
		 updatedLayout << '\n';
	}
	return true;
}