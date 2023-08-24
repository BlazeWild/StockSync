#include "AdminFrame.h"


enum IDs
{
	BUTTON_ID_ORDERS = 2,
	BUTTON_ID_SUPPLIES = 3,
	BUTTON_ID_ITEMS = 4,
	SIGNOUT_BUTTON_ID = 5
	

};

wxBEGIN_EVENT_TABLE(Admin, wxFrame)
EVT_BUTTON(BUTTON_ID_ORDERS, Admin::OnViewOrdersButtonClicked)
EVT_BUTTON(BUTTON_ID_SUPPLIES, Admin::OnViewSuppliesButtonClicked)
EVT_BUTTON(BUTTON_ID_ITEMS, Admin::OnViewItemsButtonClick)
//EVT_BUTTON(SIGNOUT_BUTTON_ID, Admin::OnSignOutButtonClick)
wxEND_EVENT_TABLE()

Admin::Admin(const wxString& title, User u1) :wxFrame(nullptr, wxID_ANY, title)
{

	//ADDING A BUTTON
	wxPanel* panel = new wxPanel(this);
	//wxButton* button = new wxButton(panel, BUTTON_ID_ADMIN, "Admin", wxPoint(400, 400), wxSize(100, 35));

	wxButton* signout_button = new wxButton(panel, SIGNOUT_BUTTON_ID, "SignOut", wxPoint(750, 10), wxSize(100, 30));
	signout_button->Bind(wxEVT_BUTTON, &Admin::OnSignOutButtonClick, this);

	// Create buttons
	wxButton* readSuppliesButton = new wxButton(panel, BUTTON_ID_SUPPLIES, "Read Supplies", wxPoint(20, 40), wxSize(100, 35));
	wxButton* readOrdersButton = new wxButton(panel, BUTTON_ID_ORDERS, "Read Orders", wxPoint(130, 40), wxSize(100, 35));
	wxButton* readItemsButton = new wxButton(panel, BUTTON_ID_ITEMS, "View Products", wxPoint(240, 40), wxSize(100, 35));

	//TITLE:
	wxStaticText* staticText1 = new wxStaticText(panel, wxID_ANY, "ADMIN PAGE", wxPoint(400, 10));


}

void Admin::OnViewOrdersButtonClicked(wxCommandEvent& evt)
{

	// Delete the previous grid if it exists
	if (dataGrid) {
		dataGrid->ClearGrid();
		delete dataGrid;
	}
	dataGrid = new wxGrid(this, wxID_ANY, wxPoint(-80, 80), wxSize(980, 500));
	dataGrid->CreateGrid(0, 10);
	int row = 0;
	for (long int OrderId = 0; OrderId < Order::order_count; ++OrderId)
	{
		wxString categoryname;
		Order order = Order::read_order_file(OrderId);
		if (order.get_order_id() != -1)
		{
			dataGrid->InsertRows(row);
			dataGrid->SetCellValue(row, 1, wxString::Format("%ld", order.get_order_id()));
			dataGrid->SetCellValue(row, 2, order.customer_name);
			dataGrid->SetCellValue(row, 3, order.product_name);
			for (long int supplyId = 0; supplyId < Supply::supply_count; supplyId++) {
				Supply supply = Supply::read_supply_file(supplyId);
				if (supply.product_name == order.product_name)
					categoryname = supply.category;
			}

			dataGrid->SetCellValue(row, 4, categoryname);
			dataGrid->SetCellValue(row, 5, wxString::Format("%d", order.quantity));
			dataGrid->SetCellValue(row, 6, wxString::Format("%d", order.rate));
			dataGrid->SetCellValue(row, 7, wxString::Format("%d", order.total_price));
			// Format and set supply date
			std::ostringstream orderDateStream;
			std::time_t orderTime = std::chrono::system_clock::to_time_t(order.get_order_date());
			orderDateStream << std::put_time(std::localtime(&orderTime), "%Y-%m-%d %H:%M:%S");
			dataGrid->SetCellValue(row, 8, orderDateStream.str());

			// Format and set delivery date
			std::ostringstream deliveryDateStream;
			std::time_t deliveryTime = std::chrono::system_clock::to_time_t(order.get_delivery_date());
			deliveryDateStream << std::put_time(std::localtime(&deliveryTime), "%Y-%m-%d %H:%M:%S");
			dataGrid->SetCellValue(row, 9, deliveryDateStream.str());
			row++;
		}
	}
	//Set Column size
	dataGrid->SetColSize(0, 30);//Index
	dataGrid->SetColSize(1, 60); //Order_ID
	dataGrid->SetColSize(2, 100); //ClientName
	dataGrid->SetColSize(3, 90);  //Product name
	dataGrid->SetColSize(4, 115);  //category
	dataGrid->SetColSize(5, 55); //quantity
	dataGrid->SetColSize(6, 90); // rate
	dataGrid->SetColSize(7, 95); // totalprice
	dataGrid->SetColSize(8, 115); // OrderDate
	dataGrid->SetColSize(9, 115); // DeliveryDate
	//Set column Names
	for (int i = 0; i < row; ++i) {
		dataGrid->SetCellValue(i, 0, wxString::Format("%d", i + 1)); // Display index starting from 1
	}
	dataGrid->SetColLabelValue(0, "SN"); // Set the label for the index column
	dataGrid->SetColLabelValue(1, "Order_ID");
	dataGrid->SetColLabelValue(2, "Customer Name");
	dataGrid->SetColLabelValue(3, "Product Name");
	dataGrid->SetColLabelValue(4, "Category");
	dataGrid->SetColLabelValue(5, "Quantity");
	dataGrid->SetColLabelValue(6, "Rate");
	dataGrid->SetColLabelValue(7, "Total Price");
	dataGrid->SetColLabelValue(8, "Supply Date");
	dataGrid->SetColLabelValue(9, "Delivery Date");

	//refreshing the grid
	dataGrid->Refresh();

}

void Admin::OnViewItemsButtonClick(wxCommandEvent& evt)
{
	// Delete the previous grid if it exists
	if (dataGrid) {
		dataGrid->ClearGrid();
		delete dataGrid;
	}
	dataGrid = new wxGrid(this, wxID_ANY, wxPoint(-80, 80), wxSize(980, 500));
	dataGrid->CreateGrid(0, 6);
	int row = 0;

	std::string prevProductName;

	// Create a map to store product name and total supplies count
	std::map<std::string, int> productSuppliesCount;
	std::map<std::string, int> productOrdersCount;
	//SET THE VALUES
// Read supplies and update supplies and orders counts
	for (long int supplyId = 0; supplyId < Supply::supply_count; ++supplyId) {
		Supply supply = Supply::read_supply_file(supplyId);
		if (supply.get_supply_id() != -1) {
			// Check if the product name is already in the grid
			int rowIndex = -1;
			for (int i = 0; i < dataGrid->GetNumberRows(); ++i) {
				wxString productNameInGrid = dataGrid->GetCellValue(i, 1); // Column index for Product Name
				if (productNameInGrid == supply.product_name) {
					rowIndex = i;
					break; // Stop searching once the product name is found
				}
			}

			// Update the quantities regardless of whether the product name is already in the grid
			productSuppliesCount[supply.product_name] += supply.quantity;

			std::string productName = supply.product_name;
			int orderCount = 0;

			// Search for the product name in the orders and update orderCount
			for (long int orderId = 0; orderId < Order::order_count; ++orderId) {
				Order order = Order::read_order_file(orderId);
				if (order.get_order_id() != -1 && order.product_name == productName) {
					orderCount += order.quantity;
				}
			}

			// Update the orders count for the product
			productOrdersCount[productName] = orderCount;
			// Calculate the count to display
			int countToDisplay = std::max(orderCount, productSuppliesCount[productName]);

			//int rowIndex = -1;
			for (int i = 0; i < dataGrid->GetNumberRows(); ++i) {
				wxString productNameInGrid = dataGrid->GetCellValue(i, 1); // Column index for Product Name
				if (productNameInGrid == supply.product_name) {
					rowIndex = i;
					break; // Stop searching once the product name is found
				}
			}


			// Update the wxGrid
			if (rowIndex != -1) {
				// Update quantities in the existing row

				dataGrid->SetCellValue(rowIndex, 3, wxString::Format("%d", productSuppliesCount[supply.product_name])); // Supplies count
				dataGrid->SetCellValue(rowIndex, 4, wxString::Format("%d", orderCount)); // Orders count

				// Calculate and set remaining in stock
				int remainingInStock = productSuppliesCount[supply.product_name] - orderCount;
				dataGrid->SetCellValue(rowIndex, 5, wxString::Format("%d", remainingInStock)); // Remaining in stock
			}
			else {
				// Insert a new row for the new product name
				dataGrid->InsertRows(row);
				dataGrid->SetCellValue(row, 1, supply.product_name);
				dataGrid->SetCellValue(row, 2, supply.category);
				// Update quantities for supplies and orders
				dataGrid->SetCellValue(row, 3, wxString::Format("%d", productSuppliesCount[supply.product_name])); // Supplies count
				dataGrid->SetCellValue(row, 4, wxString::Format("%d", orderCount)); // Orders count

				// Calculate and set remaining in stock
				int remainingInStock = productSuppliesCount[supply.product_name] - orderCount;
				dataGrid->SetCellValue(row, 5, wxString::Format("%d", remainingInStock)); // Remaining in stock

				++row;
			}

		}
	}


	// Find the row index for the product name and set the supplies count
	for (const auto& entry : productSuppliesCount) {
		int rowIndex = -1; // Initialize to -1 to indicate not found

		for (int i = 0; i < dataGrid->GetNumberRows(); ++i) {
			wxString productNameInGrid = dataGrid->GetCellValue(i, 1); // Column index for Product Name
			if (productNameInGrid == entry.first) {
				rowIndex = i;
				break; // Stop searching once the product name is found
			}
		}

		if (rowIndex != -1) {
			dataGrid->SetCellValue(rowIndex, 3, wxString::Format("%d", entry.second)); // Set the supplies count
			dataGrid->SetCellValue(rowIndex, 4, wxString::Format("%d", productOrdersCount[entry.first])); // Set the orders count
		}
	}

	//Set Column size
	dataGrid->SetColSize(0, 50);//Index
	dataGrid->SetColSize(1, 150); //Item_Name
	dataGrid->SetColSize(2, 150); //Category
	dataGrid->SetColSize(3, 120);  //Total_Supplies
	dataGrid->SetColSize(4, 120); //total orders
	dataGrid->SetColSize(5, 120);  //Remaining in Stock
	//Set column Names
	for (int i = 0; i < row; ++i) {
		dataGrid->SetCellValue(i, 0, wxString::Format("%d", i + 1)); // Display index starting from 1
	}
	dataGrid->SetColLabelValue(0, "SN"); // Set the label for the index column
	dataGrid->SetColLabelValue(1, "Product_Name");
	dataGrid->SetColLabelValue(2, "Category");
	dataGrid->SetColLabelValue(3, "Supplies Count");
	dataGrid->SetColLabelValue(4, "Orders Count");
	dataGrid->SetColLabelValue(5, "Stock Remaining");

	// Set the values for the supplies count and other columns in the grid
	for (const auto& entry : productSuppliesCount) {
		// Find the row index for the product name
		int rowIndex = -1; // You'll need to implement finding the row index based on the product name
		if (rowIndex != -1) {
			dataGrid->SetCellValue(rowIndex, 3, wxString::Format("%d", entry.second)); // Set the supplies count
			// Continue setting other values in the grid
		}
	}


	//refreshing the grid
	dataGrid->Refresh();
}



void Admin::OnViewSuppliesButtonClicked(wxCommandEvent& evt)
{
	// Delete the previous grid if it exists
	if (dataGrid) {
		dataGrid->ClearGrid();
		delete dataGrid;
	}
	dataGrid = new wxGrid(this, wxID_ANY, wxPoint(-80, 80), wxSize(980, 500));
	dataGrid->CreateGrid(0, 9);

	// Read supply data and populate the grid
	int row = 0;
	for (long int supplyId = 0; supplyId < Supply::supply_count; ++supplyId) {
		Supply supply = Supply::read_supply_file(supplyId);
		if (supply.get_supply_id() != -1) {
			dataGrid->InsertRows(row);
			dataGrid->SetCellValue(row, 1, wxString::Format("%ld", supply.get_supply_id()));
			dataGrid->SetCellValue(row, 2, supply.supplier_name);
			dataGrid->SetCellValue(row, 3, supply.product_name);
			dataGrid->SetCellValue(row, 4, supply.category);
			dataGrid->SetCellValue(row, 5, wxString::Format("%d", supply.quantity));
			dataGrid->SetCellValue(row, 6, wxString::Format("%d", supply.price));
			// Format and set supply date
			std::ostringstream supplyDateStream;
			std::time_t supplyTime = std::chrono::system_clock::to_time_t(supply.get_supply_date());
			supplyDateStream << std::put_time(std::localtime(&supplyTime), "%Y-%m-%d %H:%M:%S");
			dataGrid->SetCellValue(row, 7, supplyDateStream.str());

			// Format and set delivery date
			std::ostringstream deliveryDateStream;
			std::time_t deliveryTime = std::chrono::system_clock::to_time_t(supply.get_delivery_date());
			deliveryDateStream << std::put_time(std::localtime(&deliveryTime), "%Y-%m-%d %H:%M:%S");
			dataGrid->SetCellValue(row, 8, deliveryDateStream.str());
			row++;
		}
	}
	// Set column widths
	dataGrid->SetColSize(0, 30);//SN
	dataGrid->SetColSize(1, 60); //Supply_IDWidth
	dataGrid->SetColSize(2, 120); //supplierName
	dataGrid->SetColSize(3, 120); //productName
	dataGrid->SetColSize(4, 120); //Category
	dataGrid->SetColSize(5, 70);  //quantity
	dataGrid->SetColSize(6, 100);  //rate
	dataGrid->SetColSize(7, 120); // SupplyDate
	dataGrid->SetColSize(8, 120); // DeliveryDate

	//Set column labels
	for (int i = 0; i < row; ++i) {
		dataGrid->SetCellValue(i, 0, wxString::Format("%d", i + 1)); // Display index starting from 1
	}
	dataGrid->SetColLabelValue(0, "SN"); // Set the label for the index column
	dataGrid->SetColLabelValue(1, "Supply_ID");
	dataGrid->SetColLabelValue(2, "Supplier_Name");
	dataGrid->SetColLabelValue(3, "Product Name");
	dataGrid->SetColLabelValue(4, "Category");
	dataGrid->SetColLabelValue(5, "Quantity");
	dataGrid->SetColLabelValue(6, "Rate");
	dataGrid->SetColLabelValue(7, "Supply Date");
	dataGrid->SetColLabelValue(8, "Delivery Date");
	//refreshing after the files are deleted
	dataGrid->Refresh();
	//wxMessageBox("ViewSuppliesClicked");
}

void Admin::OnSignOutButtonClick(wxCommandEvent& evt)
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
