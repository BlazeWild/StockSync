#include "SupplierWin.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <string>


enum IDs
{
	BUTTON_ID_SUPPLIER = 2,
	SIGNOUT_BUTTON_ID = 3
};

wxBEGIN_EVENT_TABLE(SupplierWin, wxFrame)
EVT_BUTTON(BUTTON_ID_SUPPLIER, SupplierWin::OnAddItemButtonClick)
wxEND_EVENT_TABLE()

SupplierWin::SupplierWin(const wxString& title, User u1) :wxFrame(nullptr, wxID_ANY, title)
{
	u2 = u1;
	//ADDING ADD ITEM BUTTON
	wxPanel* panel = new wxPanel(this);
	wxButton* button = new wxButton(panel, BUTTON_ID_SUPPLIER, "Add Item", wxPoint(400, 400), wxSize(100, 35));

	//Add a signout button
	wxButton* signout_button = new wxButton(panel, SIGNOUT_BUTTON_ID, "SignOut", wxPoint(750, 30), wxSize(100, 35));
	signout_button->Bind(wxEVT_BUTTON, &SupplierWin::OnSignOutButtonClick, this);

	//TITLE:
	wxStaticText* staticText1 = new wxStaticText(panel, wxID_ANY, "ADD-ITEM FORM ", wxPoint(400, 50));

	//Supplier Name:
	wxString name = u1.GetName().c_str();
	wxStaticText* staticText2 = new wxStaticText(panel, wxID_ANY, "Supplier-Name: " + name, wxPoint(50, 100));
	////Product Name:
	wxStaticText* staticText3 = new wxStaticText(panel, wxID_ANY, "Product-Name: ", wxPoint(50, 150));
	textCtrl2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(200, 150), wxSize(200, -1));

	//Quantity and using Spin Control to select a number between ranges
	wxStaticText* staticText4 = new wxStaticText(panel, wxID_ANY, "Quantity: ", wxPoint(50, 200));
	spinCtrl = new wxSpinCtrl(panel, wxID_ANY, "1", wxPoint(200, 200), wxSize(100, -1));
	spinCtrl->SetRange(1, 100);

	//price:
	wxStaticText* staticText5 = new wxStaticText(panel, wxID_ANY, "Rate: ", wxPoint(50, 250));
	textCtrl3 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(200, 250), wxSize(200, -1));

	//Selecting Category
	wxStaticText* staticText6 = new wxStaticText(panel, wxID_ANY, "Select Category: ", wxPoint(50, 300));
	wxArrayString choices;
	choices.Add("Electronic Devices");
	choices.Add("Food");
	choices.Add("Books");
	choices.Add("Sports and Games");
	choices.Add("Softwares");
	choices.Add("Sports and Lifestyle");
	choices.Add("Fashion");
	choices.Add("Motors and tools");

	choice = new wxChoice(panel, wxID_ANY, wxPoint(200, 300), wxSize(200, -1), choices);
	choice->Select(0);

	//panel->Bind(wxEVT_KEY_DOWN, &SupplierWin::OnKeyEvent, this);

}
void SupplierWin::OnAddItemButtonClick(wxCommandEvent& evt)
{
	wxString productName = textCtrl2->GetValue();
	int quantity = spinCtrl->GetValue();
	long price;
	if (!textCtrl3->GetValue().ToLong(&price)) {
		wxMessageBox("Invalid price input!");
		return; // Exit the function if the conversion fails
	}
	// Get the selected category from the wxChoice control
	wxString selectedCategory = choice->GetString(choice->GetSelection());
	// Create an instance of the Supply class
	Supply supplyInstance;

	// Set the properties using the collected values
	supplyInstance.set_supply(
		u2.GetName(),  // Convert wxString to std::string
		productName.ToStdString(),    // Convert wxString to std::string
		quantity,                     // int
		static_cast<int>(price),      // Convert long to int
		selectedCategory.ToStdString()        // Convert wxString to std::string
	);


	wxMessageBox("Item Added Successfully!");
}



void SupplierWin::OnSignOutButtonClick(wxCommandEvent& evt)
{
	/*SignupFrame* signupFrameWindow = new SignupFrame("Signup/Login");
	signupFrameWindow->Show();
	this->Close();*/
	wxMessageBox("Signed-Out successfully!");
	// Close the current ClientFrame window
	Close();
	// Create and show a new instance of the LoginFrame window
	LoginFrame* loginFrame = new LoginFrame("StockSync");
	loginFrame->SetClientSize(800, 800);
	loginFrame->Center();
	loginFrame->Show();
}
