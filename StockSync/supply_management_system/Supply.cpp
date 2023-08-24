#include "Supply.h"

long get_supply_count() {
    std::ifstream file("supply_count.txt");
    if (!file) {
        return 0;
    }
    long int count;
    file >> count;
    file.close();
    return count;
}

void set_supply_count(long int count) {
    std::ofstream file("supply_count.txt");
    std::cout << "fuck" << std::endl;
    file << count;
    file.close();
}

long int Supply::supply_count = get_supply_count();

void Supply::set_supply() {
    //supply_id = supply_count++;
    //is_cancelled = false;
    //is_delivered = false;
    //is_accepted = false;
    //supply_date = std::chrono::system_clock::now();
    //delivery_date = std::chrono::system_clock::now() + std::chrono::hours(24 * 5);
    //std::cout << "Enter the name of the supplier: ";
    //std::cin >> supplier_name;
    //std::cout << "Enter the item details: " << std::endl;
    //std::cout << "Enter name of the product: ";
    //std::cin >> product_name;
    //std::cout << "Enter quantity: ";
    //std::cin >> quantity;
    //std::cout << "Enter price: ";
    //std::cin >> price;
    //std::cout << "Enter category: ";
    //std::cin >> category;

    //// std::cout << "Enter the items: " << std::endl;
    //// char ch = 'y';
    //// while(ch == 'y' || ch == 'Y'){
    ////     Item item;
    ////     item.set_item();
    ////     items.push_back(item);
    ////     std::cout << "Do you want to add more items? (y/n): ";
    ////     std::cin >> ch;
    //// }
    //save_to_file();
}

void Supply::set_supply(std::string supplier_name_, std::string name_, int quantity_, int price_, std::string category_) {
    supply_id = supply_count++;
    is_cancelled = false;
    is_delivered = false;
    is_accepted = false;
    supply_date = std::chrono::system_clock::now();
    delivery_date = std::chrono::system_clock::now() + std::chrono::hours(24 * 5);
    supplier_name = supplier_name_;
    product_name = name_;
    quantity = quantity_;
    price = price_;
    category = category_;
    save_to_file();
    set_supply_count(supply_count);

}

void Supply::set_is_delivered(bool is_delivered_) {
    is_delivered = is_delivered_;
    save_to_file();
}

void Supply::set_is_cancelled(bool is_cancelled_) {
    is_cancelled = is_cancelled_;
    save_to_file();
}

void Supply::set_is_accepted(bool is_accepted_) {
    is_accepted = is_accepted_;
    save_to_file();
}

bool Supply::get_is_delivered() {
    return is_delivered;
}

bool Supply::get_is_cancelled() {
    return is_cancelled;
}

bool Supply::get_is_accepted() {
    return is_accepted;
}

void Supply::set_delivery_date() {
    delivery_date = get_date();
    save_to_file();
}

void Supply::set_delivery_date(std::chrono::system_clock::time_point date) {
    delivery_date = date;
    save_to_file();
}

std::chrono::system_clock::time_point Supply::get_delivery_date() {
    return delivery_date;
}

std::chrono::system_clock::time_point Supply::get_supply_date() {
    return supply_date;
}

long int Supply::get_supply_id() {
    return supply_id;
}

void Supply::save_to_file() {
    std::ofstream file;
    file.open("../StockSync/supply_management_system/supplies/" + std::to_string(supply_id) + ".txt", std::ios::binary);
    if (!file) {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    // file.write(reinterpret_cast <char*> (this), sizeof(Supply));

    file.write(reinterpret_cast<const char*>(&supply_id), sizeof(supply_id));
    file.write(reinterpret_cast<const char*>(&is_delivered), sizeof(is_delivered));
    file.write(reinterpret_cast<const char*>(&is_cancelled), sizeof(is_cancelled));
    file.write(reinterpret_cast<const char*>(&is_accepted), sizeof(is_accepted));

    std::string::size_type supplierNameSize = supplier_name.size();
    file.write(reinterpret_cast<const char*>(&supplierNameSize), sizeof(supplierNameSize));
    file.write(supplier_name.c_str(), supplierNameSize);

    file.write(reinterpret_cast<const char*>(&supply_date), sizeof(supply_date));
    file.write(reinterpret_cast<const char*>(&delivery_date), sizeof(delivery_date));

    std::string::size_type productNameSize = product_name.size();
    file.write(reinterpret_cast<const char*>(&productNameSize), sizeof(productNameSize));
    file.write(product_name.c_str(), productNameSize);

    file.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
    file.write(reinterpret_cast<const char*>(&price), sizeof(price));

    std::string::size_type categorySize = category.size();
    file.write(reinterpret_cast<const char*>(&categorySize), sizeof(categorySize));
    file.write(category.c_str(), categorySize);

    file.close();
    std::cout << "Supply saved to file" << std::endl;
}

Supply Supply::read_supply_file(long int supply_id) {
    std::cout << "reading supply of id " << supply_id << std::endl;
    Supply supply;
    std::ifstream file;
    file.open("../StockSync/supply_management_system/supplies/" + std::to_string(supply_id) + ".txt", std::ios::binary);
    if (!file) {
        std::cout << "Error opening file" << std::endl;
        return supply;
    }
    // file.read(reinterpret_cast <char*> (&supply), sizeof(Supply));

    file.read(reinterpret_cast<char*>(&supply.supply_id), sizeof(supply.supply_id));
    file.read(reinterpret_cast<char*>(&supply.is_delivered), sizeof(supply.is_delivered));
    file.read(reinterpret_cast<char*>(&supply.is_cancelled), sizeof(supply.is_cancelled));
    file.read(reinterpret_cast<char*>(&supply.is_accepted), sizeof(supply.is_accepted));

    std::string::size_type supplierNameSize;
    file.read(reinterpret_cast<char*>(&supplierNameSize), sizeof(supplierNameSize));
    char supplierNameBuffer[100];
    file.read(supplierNameBuffer, supplierNameSize);
    supplierNameBuffer[supplierNameSize] = '\0';
    supply.supplier_name = std::string(supplierNameBuffer);

    file.read(reinterpret_cast<char*>(&supply.supply_date), sizeof(supply.supply_date));
    file.read(reinterpret_cast<char*>(&supply.delivery_date), sizeof(supply.delivery_date));

    std::string::size_type productNameSize;
    file.read(reinterpret_cast<char*>(&productNameSize), sizeof(productNameSize));
    char productNameBuffer[100];
    file.read(productNameBuffer, productNameSize);
    productNameBuffer[productNameSize] = '\0';
    supply.product_name = std::string(productNameBuffer);

    file.read(reinterpret_cast<char*>(&supply.quantity), sizeof(supply.quantity));
    file.read(reinterpret_cast<char*>(&supply.price), sizeof(supply.price));

    std::string::size_type categorySize;
    file.read(reinterpret_cast<char*>(&categorySize), sizeof(categorySize));
    char categoryBuffer[100];
    file.read(categoryBuffer, categorySize);
    categoryBuffer[categorySize] = '\0';
    supply.category = std::string(categoryBuffer);


    file.close();
    std::cout << supply;
    return supply;
}


std::ostream& operator<<(std::ostream& os, const Supply& supply) {
    std::cout << "Supply Details: " << std::endl;
    os << "Supply ID: " << supply.supply_id << std::endl;
    os << "Supplier Name: " << supply.supplier_name << std::endl;
    os << "Supply Date: " << get_printable_date(supply.supply_date) << std::endl;
    os << "Delivery Date: " << get_printable_date(supply.delivery_date) << std::endl;
    os << "Product details: " << std::endl;
    os << "Name: " << supply.product_name << std::endl;
    os << "Quantity: " << supply.quantity << std::endl;
    os << "Price: " << supply.price << std::endl;
    os << "Category: " << supply.category << std::endl;
    return os;
}
