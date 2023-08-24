#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "./loginPage/SignupFrame.h"
#include "./loginPage/LoginFrame.h"
#include "./supply_management_system/Supply.h"
#include"./loginPage/main.h"

class SupplierWin :public wxFrame
{
private:
	wxTextCtrl* textCtrl2; //product name
	wxSpinCtrl* spinCtrl;//quantity
	wxTextCtrl* textCtrl3;//price
	wxChoice* choice;
	User u2;

	enum
	{
		ID_PRODUCT_NAME = wxID_HIGHEST + 1,
		ID_PRODUCT_NAME_2
	};
	void OnAddItemButtonClick(wxCommandEvent& evt);
	void OnSignOutButtonClick(wxCommandEvent& evt);
	//void OnKeyEvent(wxKeyEvent& evt);

public:

	SupplierWin(const wxString& title, User u1);
	wxDECLARE_EVENT_TABLE();
};
