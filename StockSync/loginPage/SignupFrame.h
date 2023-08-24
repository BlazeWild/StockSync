#pragma once
#include<wx/wx.h>
class SignupFrame:public wxFrame
{
private:
	wxTextCtrl* nameTextCtrl;
	wxTextCtrl* addressTextCtrl;
	wxComboBox* userRoleTextCtrl;
	wxTextCtrl* usernameTextCtrl;
	wxTextCtrl* passwordTextCtrl;
	void OnSubmitButtonClicked(wxCommandEvent& evt);
	void OnLoginButtonClicked(wxCommandEvent& evt);

public:
	SignupFrame(const wxString& title);
};

