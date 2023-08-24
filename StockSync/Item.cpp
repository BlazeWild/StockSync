#include "Item.h"
#include "util.h"

Item::Item(std::string name_, std::string description_, float weight_, int price_, int quantity_, std::string category_, std::chrono::system_clock::time_point expiration_date_)
: name(name_), description(description_), weight(weight_), price(price_), quantity(quantity_), category(category_), expiration_date(expiration_date_) {
    item_id = item_count++;
    listed_date = std::chrono::system_clock::now();
    // save_to_file();
}
long int get_item_count() {
    std::ifstream file;
    file.open("item_count.txt");
    if (!file) {
        return 0;
    }
    long count;
    file >> count;
    file.close();
    return count;
}

void set_item_count(long count) {
    std::ofstream file;
    file.open("item_count.txt");
    file << count;
    file.close();
}
long Item::item_count = get_item_count();

void Item::set_item(std::string name_, std::string description_, float weight_, int price_, int quantity_, std::string category_){
    item_id = item_count++;
    name = name_;
    description = description_;
    weight = weight_;
    price = price_;
    quantity = quantity_;
    category = category_;
    listed_date = std::chrono::system_clock::now();
    // save_to_file();
    set_item_count(item_count);
}

long int Item::get_id() {
    return item_id;
}

//long int Item::item_count = 0;

float Item::get_weight(){
    return weight;
}

int Item::get_price(){
    return price;
}

int Item::get_quantity(){
    return quantity;
}

std::string Item::get_category(){
    return category;
}

std::chrono::system_clock::time_point Item::get_listed_date(){
    return listed_date;
}

std::chrono::system_clock::time_point Item::get_expiration_date(){
    return expiration_date;
}


std::ostream& operator<<(std::ostream &os, const Item& item){
    os << "Item ID: " << item.item_id << std::endl;
    os << "Name: " << item.name << std::endl;
    os << "Description: " << item.description << std::endl;
    os << "Weight: " << item.weight << std::endl;
    os << "Price: " << item.price << std::endl;
    os << "Quantity: " << item.quantity << std::endl;
    os << "Category: " << item.category << std::endl;
    os << "Listed Date: " << get_printable_date(item.listed_date) << std::endl;
    os << "Expiration Date: " << get_printable_date(item.expiration_date) << std::endl;
    return os;
}
