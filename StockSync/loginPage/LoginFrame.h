#pragma once
#include<wx/wx.h>
#include"SignupFrame.h"
#include"../SupplierWin.h"
#include"../ClientFrame.h"
#include"../AdminFrame.h"


class LoginFrame :public wxFrame
{
private:
	wxTextCtrl* usernameTextCtrl;
	wxTextCtrl* passwordTextCtrl;
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnSignupButtonClicked(wxCommandEvent& evt);

public:
	LoginFrame(const wxString& title);

};

