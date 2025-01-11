#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	MainFrame* mainFrame = new MainFrame("Monster Jam: Urban Assault (DS) Autosplitter Configuration");
	mainFrame->SetClientSize(660, 350);			//
	mainFrame->SetMinSize(wxSize(660, 350));	//
	mainFrame->SetMaxSize(wxSize(660, 350));	//
	mainFrame->EnableMaximizeButton(false);		// disables resizing/maximizing the window
	mainFrame->Center();
	mainFrame->Show();
	return true;
}