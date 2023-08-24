#include "SignupFrame.h"
#include "main.h"
#include <wx/wx.h>
#include "LoginFrame.h"

SignupFrame::SignupFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel *panel = new wxPanel(this);

	wxStaticText *NameLabel = new wxStaticText(panel, wxID_ANY, "Name", wxPoint(250, 220));
	nameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 220), wxSize(200, -1));

	wxStaticText *AddressLabel = new wxStaticText(panel, wxID_ANY, "Address", wxPoint(250, 255));
	addressTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 255), wxSize(200, -1));

	wxString choices[] = {"Admin", "Supplier", "Client"};
	userRoleTextCtrl = new wxComboBox(panel, wxID_ANY, "Admin", wxPoint(250, 285), wxDefaultSize, 3, choices, wxCB_DROPDOWN);

	wxStaticText *usernameLabel = new wxStaticText(panel, wxID_ANY, "Username", wxPoint(250, 320));
	usernameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 320), wxSize(200, -1));

	wxStaticText *passwordLabel = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(250, 355));
	passwordTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 355), wxSize(200, -1), wxTE_PASSWORD);

	wxButton *submitButton = new wxButton(panel, wxID_ANY, "Signup", wxPoint(250, 420), wxSize(100, 35));
	wxButton *loginButton = new wxButton(panel, wxID_ANY, "Login", wxPoint(355, 420), wxSize(100, 35));

	submitButton->Bind(wxEVT_BUTTON, &SignupFrame::OnSubmitButtonClicked, this);
	loginButton->Bind(wxEVT_BUTTON, &SignupFrame::OnLoginButtonClicked, this);

	CreateStatusBar();
}

void SignupFrame::OnSubmitButtonClicked(wxCommandEvent &evt)
{
	wxLogStatus("Button clicked");
	wxString name = nameTextCtrl->GetValue();
	wxString address = addressTextCtrl->GetValue();
	wxString userRole = userRoleTextCtrl->GetValue();
	wxString username = usernameTextCtrl->GetValue();
	wxString password = passwordTextCtrl->GetValue();
	std::string Name = name.ToStdString();
	std::string Address = address.ToStdString();
	std::string UserRole = userRole.ToStdString();
	std::string Username = username.ToStdString();
	std::string Password = password.ToStdString();

	bool containsSpecialChar = false;
	bool containsNumber = false;
	bool containsUppercase = false;

	for (char c : password)
	{
		if (std::isalnum(c))
		{
			if (std::isdigit(c))
			{
				containsNumber = true;
			}
			else if (std::isupper(c))
			{
				containsUppercase = true;
			}
		}
		else
		{
			containsSpecialChar = true;
		}
	}
	if (Name.length() != 0 && Address.length() && Username.length() != 0 && Password.length() != 0)
	{
		if (Password.length() >= 8)
		{
			if (containsSpecialChar && containsNumber && containsUppercase)
			{
				User s1(Name, Address, UserRole, Username, Password);
				s1.AddUser();
				wxMessageBox("signup successfully", "Login Info", wxOK | wxICON_INFORMATION);
			}
			else
			{
				wxMessageBox("enter at least one uppercase,one number and one special character", "Login Info", wxOK | wxICON_INFORMATION);
			}
		}
		else
		{
			wxMessageBox("password should contain at least 8 character", "Login Info", wxOK | wxICON_INFORMATION);
		}
	}
	else
	{
		wxMessageBox("please fill all the form", "Login Info", wxOK | wxICON_INFORMATION);
	}

	wxLogStatus(username);
}
void SignupFrame::OnLoginButtonClicked(wxCommandEvent &evt)
{
	Close();
	LoginFrame *loginFrame = new LoginFrame("StockSync");
	loginFrame->SetClientSize(800, 800);
	loginFrame->Center();
	loginFrame->Show();
}