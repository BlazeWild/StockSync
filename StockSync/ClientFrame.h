#pragma once
#include <wx/wx.h>
#include <string>
#include <wx/spinctrl.h>
#include <wx/grid.h>
#include"loginPage/main.h"
#include "order_management_system/OrderManagement.h"
#include "supply_management_system/supply.h"
#include "order_management_system/Order.h"
#include "loginPage/LoginFrame.h"

//Inheriting ClientFrame Class From wxFrame class
class ClientFrame :public wxFrame
{
private:
	User u2;
	std::vector<std::string>productList;
	wxArrayString ProductList;
	long int rate;
	long int totalPrice = 0;
	wxStaticText* staticText;
	wxButton* signout_button;
	wxButton* buyItems_button;
	wxButton* seeDetails_button;
	wxComboBox* productchoice;
	wxSpinCtrl* spinCtrl;
	wxComboBox* choice;
	wxGrid* dataGrid;
	void OnBuyItemsButtonClicked(wxCommandEvent& evt);
	void OnSeeDetailsButtonClicked(wxCommandEvent& evt);
	void OnButtonClicked(wxCommandEvent& evt);
	void OnSignOutButtonClicked(wxCommandEvent& evt);
	void OnChoiceSelected(wxCommandEvent& event);
	void OnProductChoiceSelected(wxCommandEvent& event);
	void OnSpinCtrlChange(wxSpinEvent& event);
	wxPanel* newpanel;
	wxPanel* detailspanel;
	


public:
	ClientFrame(const wxString& title, User u1);

	

};

