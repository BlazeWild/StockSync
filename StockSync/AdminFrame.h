#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/grid.h>
#include <wx/dir.h>
#include <string>
#include<map>
#include "./supply_management_system/Supply.h"
#include "./order_management_system/Order.h"
#include "./loginPage/SignupFrame.h"
#include "./loginPage/LoginFrame.h"
#include "./supply_management_system/Supply.h"
#include"./loginPage/main.h"

class Admin :public wxFrame
{
private:
	wxTextCtrl* textCtrl1;
	wxGrid* dataGrid;

	enum
	{
		ID_PRODUCT_NAME = wxID_HIGHEST + 1,
		ID_PRODUCT_NAME_2
	};
	void OnViewOrdersButtonClicked(wxCommandEvent& evt);
	void OnViewSuppliesButtonClicked(wxCommandEvent& evt);
	void OnViewItemsButtonClick(wxCommandEvent& evt);
	void OnSignOutButtonClick(wxCommandEvent& evt);
	void OnKeyEvent(wxKeyEvent& evt);

public:

	Admin(const wxString& title, User u1);
	wxDECLARE_EVENT_TABLE();
};
