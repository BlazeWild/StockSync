//Mainframe.cpp
#include "LoginFrame.h"
#include "../ClientFrame.h"
#include "../AdminFrame.h"
#include "../SupplierWin.h"
#include"main.h"
#include<wx/wx.h>
#include"SignupFrame.h"

LoginFrame::LoginFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);


	wxStaticText* usernameLabel = new wxStaticText(panel, wxID_ANY, "Username", wxPoint(250, 150));
	usernameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 150), wxSize(200, -1));
	wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(250, 220));
	passwordTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 220), wxSize(200, -1), wxTE_PASSWORD);
	wxButton* submitButton = new wxButton(panel, wxID_ANY, "Login", wxPoint(250, 255), wxSize(100, 35));
	wxButton* signupButton = new wxButton(panel, wxID_ANY, "signup", wxPoint(355, 255), wxSize(100, 35));

	submitButton->Bind(wxEVT_BUTTON, &LoginFrame::OnLoginButtonClicked, this);
	signupButton->Bind(wxEVT_BUTTON, &LoginFrame::OnSignupButtonClicked, this);
	CreateStatusBar();
}

void LoginFrame::OnLoginButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Button clicked");
	wxString username = usernameTextCtrl->GetValue();
	wxString password = passwordTextCtrl->GetValue();
	std::string Username = username.ToStdString();
	std::string Password = password.ToStdString();


	User s1;
	User s2 = s1.AuthenticateUser(Username, Password);
	if (!s2.IsEmpty())
	{
		wxMessageBox("login successfully", "Login Info", wxOK | wxICON_INFORMATION);
		//close the login window
		Close();
		// Open the ClientFrame window here
		if (s2.GetUserRole() == "Admin")
		{
			// Open Admin Window
			Admin* adminWindow = new Admin("Admin Window",s2);
			adminWindow->SetClientSize(900, 600);
			adminWindow->Center();
			adminWindow->Show();
		}

		else if (s2.GetUserRole() == "Supplier")
		{
			//Open supplier window
			SupplierWin* supplierwin = new SupplierWin("Supplier Window",s2);
			supplierwin->SetClientSize(900, 600);
			supplierwin->Center();
			supplierwin->Show();
		}
		else if (s2.GetUserRole() == "Client")
		{
			// Open Set Order Window
			ClientFrame* ClientFrameWindow = new ClientFrame("Set Order",s2);
			ClientFrameWindow->SetClientSize(900, 600);
			ClientFrameWindow->Center();
			ClientFrameWindow->Show();
		}

		/*ClientFrame* ClientFrameWindow = new ClientFrame("Set Order");
		ClientFrameWindow->Show();*/


	}
	else {
		wxMessageBox("wrong username or password", "Login Info", wxOK | wxICON_INFORMATION);
	}
}
void LoginFrame::OnSignupButtonClicked(wxCommandEvent& evt) {
	Close();
	SignupFrame* signupFrame = new SignupFrame("StockSync");
	signupFrame->SetClientSize(800, 800);
	signupFrame->Center();
	signupFrame->Show();
}
