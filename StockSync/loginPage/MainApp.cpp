#include "MainApp.h"
#include"LoginFrame.h"
#include<wx/wx.h>

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit() {
	LoginFrame* loginFrame = new LoginFrame("StockSync");
	loginFrame->SetClientSize(800, 800);
	loginFrame->Center();
	loginFrame->Show();
	return true;
}
