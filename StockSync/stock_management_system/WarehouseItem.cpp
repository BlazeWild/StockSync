//#include "WarehouseItem.h"
//
//void WarehouseItem::set_item()
//{
//    Item::set_item();
//    save_to_file();
//}
//
//void WarehouseItem::set_item(std::string name_, std::string description_, float weight_, int price_, int quantity_, std::string category_)
//{
//    Item::set_item(name_, description_, weight_, price_, quantity_, category_);
//    save_to_file();
//}
//
//WarehouseItem WarehouseItem::read_item_file(long int item_id_)
//{
//    std::cout << "Reading warehouseItem file " << item_id_ << std::endl;
//    std::ifstream file;
//    WarehouseItem warehouseItem;
//    file.open("stock_management_system/items/" + std::to_string(item_id_) + ".txt", std::ios::binary);
//    if (!file)
//    {
//        std::cout << "Error opening file" << std::endl;
//        return warehouseItem;
//    }
//    // file.read(reinterpret_cast <char*> (&warehouseItem), sizeof(WarehouseItem));
//
//    file.read(reinterpret_cast<char *>(&warehouseItem.item_id), sizeof(warehouseItem.item_id));
//
//    std::string::size_type nameSize;
//    file.read(reinterpret_cast<char *>(&nameSize), sizeof(nameSize));
//    char buffer[100];
//    file.read(buffer, nameSize);
//    buffer[nameSize] = '\0';
//    warehouseItem.name = std::string(buffer);
//
//    std::string::size_type descriptionSize;
//    file.read(reinterpret_cast<char *>(&descriptionSize), sizeof(descriptionSize));
//    file.read(buffer, descriptionSize);
//    buffer[descriptionSize] = '\0';
//    warehouseItem.description = std::string(buffer);
//
//    file.read(reinterpret_cast<char *>(&warehouseItem.weight), sizeof(warehouseItem.weight));
//    file.read(reinterpret_cast<char *>(&warehouseItem.price), sizeof(warehouseItem.price));
//    file.read(reinterpret_cast<char *>(&warehouseItem.quantity), sizeof(warehouseItem.quantity));
//
//    std::string::size_type categorySize;
//    file.read(reinterpret_cast<char *>(&categorySize), sizeof(categorySize));
//    file.read(buffer, categorySize);
//    buffer[categorySize] = '\0';
//    warehouseItem.category = std::string(buffer);
//
//    file.read(reinterpret_cast<char *>(&warehouseItem.listed_date), sizeof(warehouseItem.listed_date));
//    file.read(reinterpret_cast<char *>(&warehouseItem.expiration_date), sizeof(warehouseItem.expiration_date));
//
//    file.close();
//    std::cout << warehouseItem << std::endl;
//    return warehouseItem;
//}
//
//void WarehouseItem::save_to_file()
//{
//    std::ofstream file;
//    file.open("stock_management_system/items/" + std::to_string(item_id) + ".txt", std::ios::binary);
//    if (!file)
//    {
//        std::cout << "Error opening file" << std::endl;
//        return;
//    }
//
//    // file.write(reinterpret_cast <char*>(this), sizeof(Item));
//
//    file.write(reinterpret_cast<const char *>(&item_id), sizeof(item_id));
//
//    std::string::size_type nameSize = name.size();
//    file.write(reinterpret_cast<const char *>(&nameSize), sizeof(nameSize));
//    file.write(name.c_str(), nameSize);
//
//    std::string::size_type descriptionSize = description.size();
//    file.write(reinterpret_cast<const char *>(&descriptionSize), sizeof(descriptionSize));
//    file.write(description.c_str(), descriptionSize);
//
//    file.write(reinterpret_cast<const char *>(&weight), sizeof(weight));
//    file.write(reinterpret_cast<const char *>(&price), sizeof(price));
//    file.write(reinterpret_cast<const char *>(&quantity), sizeof(quantity));
//
//    std::string::size_type categorySize = category.size();
//    file.write(reinterpret_cast<const char *>(&categorySize), sizeof(categorySize));
//    file.write(category.c_str(), categorySize);
//
//    file.write(reinterpret_cast<const char *>(&listed_date), sizeof(listed_date));
//    file.write(reinterpret_cast<const char *>(&expiration_date), sizeof(expiration_date));
//    file.close();
//    std::cout << "Item saved to file" << std::endl;
//}
