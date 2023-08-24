#include "ClientFrame.h"


ClientFrame::ClientFrame(const wxString& title, User u1) :wxFrame(nullptr, wxID_ANY, title)
{
	u2 = u1;

	wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);

	newpanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
	detailspanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
	newpanel->Hide();
	detailspanel->Hide();

	//Add a signout button
	signout_button = new wxButton(panel, wxID_ANY, "SignOut",wxPoint(750, 20), wxSize(100, 35));
	buyItems_button = new wxButton(panel, wxID_ANY, "Buy Items", wxPoint(150, 50), wxSize(100, 35));
	seeDetails_button = new wxButton(panel, wxID_ANY, "See Details", wxPoint(250, 50), wxSize(100, 35));

	signout_button->Bind(wxEVT_BUTTON, &ClientFrame::OnSignOutButtonClicked, this);
	buyItems_button->Bind(wxEVT_BUTTON, &ClientFrame::OnBuyItemsButtonClicked, this);
	seeDetails_button->Bind(wxEVT_BUTTON, &ClientFrame::OnSeeDetailsButtonClicked, this);


wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
mainSizer->Add(panel, 0, wxEXPAND);
mainSizer->Add(newpanel, 1, wxEXPAND); // Expand to fill available space
mainSizer->Add(detailspanel, 1, wxEXPAND); // Expand to fill available space
SetSizer(mainSizer);


}

void ClientFrame::OnBuyItemsButtonClicked(wxCommandEvent& evt) {
	while (detailspanel->GetChildren().GetCount() > 0) {
		wxWindow* child = detailspanel->GetChildren()[0];
		detailspanel->RemoveChild(child);
		delete child;
	}
	detailspanel->Hide();
	
	newpanel->Show();
	wxString name = u2.GetName().c_str();
	wxStaticText* staticText1 = new wxStaticText(newpanel, wxID_ANY, "Customer-Name: " + name, wxPoint(50, 55));


	wxButton* button = new wxButton(newpanel, wxID_ANY, "Buy Now", wxPoint(400, 400), wxSize(100, 35));
	button->Bind(wxEVT_BUTTON, &ClientFrame::OnButtonClicked, this);

	wxStaticText* staticText3 = new wxStaticText(newpanel, wxID_ANY, "Select Category: ", wxPoint(50, 85));

	wxArrayString choices;
	choices.Add("Electronic Devices");
	choices.Add("Food");
	choices.Add("Books");
	choices.Add("Sports and Games");
	choices.Add("Softwares");
	choices.Add("Sports and Lifestyle");
	choices.Add("Fashion");
	choices.Add("Motors and tools");

choice = new wxComboBox(newpanel, wxID_ANY, wxEmptyString, wxPoint(200, 85), wxSize(200, -1), 0, NULL, wxCB_DROPDOWN);
choice->Append(choices);
	choice->Select(0);

	choice->Bind(wxEVT_COMBOBOX, &ClientFrame::OnChoiceSelected, this); // Bind the event

	//Product Name:



	//Product:
	wxStaticText* staticText2 = new wxStaticText(newpanel, wxID_ANY, "Product-Name: ", wxPoint(50, 150));
	productchoice = new wxComboBox(newpanel, wxID_ANY, wxEmptyString, wxPoint(200, 150), wxSize(200, -1),
		0, NULL, wxCB_DROPDOWN);
	productchoice->Select(0);
	productchoice->Bind(wxEVT_COMBOBOX, &ClientFrame::OnProductChoiceSelected, this); // Bind the event

	//Quantity and using Spin Control to select a number between ranges
	wxStaticText* staticText4 = new wxStaticText(newpanel, wxID_ANY, "Quantity: ", wxPoint(50, 200));
	spinCtrl = new wxSpinCtrl(newpanel, wxID_ANY, "0", wxPoint(200, 200), wxSize(100, -1));
	spinCtrl->Bind(wxEVT_SPINCTRL, &ClientFrame::OnSpinCtrlChange, this);

	wxString displaytext = wxString::Format("Total Price: %ld", totalPrice);
	staticText = new wxStaticText(newpanel, wxID_ANY,displaytext, wxPoint(50, 250));

	this->Layout();


}

void ClientFrame::OnSpinCtrlChange(wxSpinEvent& event) {
	int quantity = spinCtrl->GetValue();
	totalPrice = rate * quantity;
	wxString displaytext = wxString::Format("Total Price: %ld", totalPrice);
	staticText->SetLabel(displaytext);
}

void ClientFrame::OnSeeDetailsButtonClicked(wxCommandEvent& evt) {
	while (newpanel->GetChildren().GetCount() > 0) {
		wxWindow* child = newpanel->GetChildren()[0];
		newpanel->RemoveChild(child);
		delete child;
	}
	newpanel->Hide();
	detailspanel->Show();
	// Set column sizes to default
	
	dataGrid = new wxGrid(detailspanel, wxID_ANY, wxPoint(-80, 20), wxSize(900, 500));
	dataGrid->CreateGrid(0, 9);
	int row = 0;
	for (long int OrderId = 0; OrderId < Order::order_count; ++OrderId)
	{
		wxString categoryname;
		Order order = Order::read_order_file(OrderId);
		if (order.get_order_id() != -1)
		{
			if (order.customer_name == u2.GetName()) {
				dataGrid->InsertRows(row);
				dataGrid->SetCellValue(row, 1, wxString::Format("%ld", order.get_order_id()));
				dataGrid->SetCellValue(row, 2, order.product_name);

				for (long int supplyId = 0; supplyId < Supply::supply_count; supplyId++) {
					Supply supply = Supply::read_supply_file(supplyId);
					if (supply.product_name == order.product_name)
						categoryname = supply.category;
				}

				dataGrid->SetCellValue(row, 3, categoryname);
				dataGrid->SetCellValue(row, 4, wxString::Format("%d", order.quantity));
				dataGrid->SetCellValue(row, 5, wxString::Format("%d",order.rate));
				dataGrid->SetCellValue(row, 6, wxString::Format("%d",order.total_price));
				// Format and set supply date
				std::ostringstream orderDateStream;
				std::time_t orderTime = std::chrono::system_clock::to_time_t(order.get_order_date());
				orderDateStream << std::put_time(std::localtime(&orderTime), "%Y-%m-%d %H:%M:%S");
				dataGrid->SetCellValue(row, 7, orderDateStream.str());

				// Format and set delivery date
				std::ostringstream deliveryDateStream;
				std::time_t deliveryTime = std::chrono::system_clock::to_time_t(order.get_delivery_date());
				deliveryDateStream << std::put_time(std::localtime(&deliveryTime), "%Y-%m-%d %H:%M:%S");
				dataGrid->SetCellValue(row, 8, deliveryDateStream.str());
				row++;
			}
			
		}
	}
	//Set Column size
	dataGrid->SetColSize(0, 30);//Index
	dataGrid->SetColSize(1, 60); //Order_ID
	dataGrid->SetColSize(2, 100); //Product name
	dataGrid->SetColSize(3, 110);  //category
	dataGrid->SetColSize(4, 60);  //quantity
	dataGrid->SetColSize(5, 90); // rate
	dataGrid->SetColSize(6, 115); // totalprice
	dataGrid->SetColSize(7, 115); // OrderDate
	dataGrid->SetColSize(8, 115); // DeliveryDate


	//Set column Names
	for (int i = 0; i < row; ++i) {
		dataGrid->SetCellValue(i, 0, wxString::Format("%d", i + 1)); // Display index starting from 1
	}
	dataGrid->SetColLabelValue(0, "SN"); // Set the label for the index column
	dataGrid->SetColLabelValue(1, "Order_ID");
	dataGrid->SetColLabelValue(2, "Product Name");
	dataGrid->SetColLabelValue(3, "Category");
	dataGrid->SetColLabelValue(4, "Quantity");
	dataGrid->SetColLabelValue(5, "Rate");
	dataGrid->SetColLabelValue(6, "Total Price");
	dataGrid->SetColLabelValue(7, "Supply Date");
	dataGrid->SetColLabelValue(8, "Delivery Date");

	//refreshing the grid
	dataGrid->Refresh();
	this->Layout();
}

void ClientFrame::OnChoiceSelected(wxCommandEvent& event) {

		wxString selectedText = event.GetString();
		std::string selectedChoice = selectedText.ToStdString();
		productchoice->Clear();

		for (long int supplyId = 0; supplyId < Supply::supply_count; supplyId++) {
			Supply supply = Supply::read_supply_file(supplyId);
				if (supply.category == selectedChoice) {
					rate = supply.price;
					productchoice->Append(supply.product_name);
				}
		}
		productchoice->Select(0);


}

void ClientFrame::OnProductChoiceSelected(wxCommandEvent& event) {
	wxString productchoice = event.GetString();
	std::string productname = productchoice.ToStdString();

	wxString selectedText = event.GetString();
	std::string selectedChoice = selectedText.ToStdString();

	for (long int supplyId = 0; supplyId < Supply::supply_count; supplyId++) {
		Supply supply = Supply::read_supply_file(supplyId);
		if (supply.category == selectedChoice) {
			if(supply.product_name==productname)
				rate = supply.price;
		}
	}
}

void ClientFrame::OnButtonClicked(wxCommandEvent& evt)
{
	// Extract input values from GUI elements
	int selectedIndex = productchoice->GetSelection();
	wxString productName = productchoice->GetString(selectedIndex);

	int quantity = spinCtrl->GetValue();

	//Convert wxString values to std::string
	std::string stdProductName = std::string(productName.mb_str());

	OrderManagement order_management;
	order_management.place_order(u2.GetName(), stdProductName, quantity,rate,totalPrice);


	//To read the order details back and display them
	Order order1 = order_management.read_order_file(0);


	wxLogMessage("Order placed successfully!");
	////for debugging
	//wxLogMessage("Customer: %s, Product: %s, Quantity: %d", customerName, productName, quantity);
}

//close ClientFrame Window and go to login/signup page
void ClientFrame::OnSignOutButtonClicked(wxCommandEvent& evt)
{
	Close();
	LoginFrame* loginFrame = new LoginFrame("StockSync");
	loginFrame->SetClientSize(800, 800);
	loginFrame->Center();
	loginFrame->Show();


}