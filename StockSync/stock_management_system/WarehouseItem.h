//#ifndef WarehouseItem_H
//#define WarehouseItem_H
//
//#pragma once
//#include<iostream>
//#include<fstream>
//#include "../Item.h"
//#include "../util.h"
//class WarehouseItem: public Item{
//    public:
//        WarehouseItem(std::string name_, std::string description_, float weight_, int price_, int quantity_, std::string category_, std::chrono::system_clock::time_point expiration_date_){
//            item_id = item_count++;
//            listed_date = std::chrono::system_clock::now();
//            Item(name_, description_, weight_, price_, quantity_, category_, expiration_date_);
//            save_to_file();
//        }
//
//        WarehouseItem(){};
//
//        static WarehouseItem read_item_file(long int id);
//
//        void set_item();
//    
//        void set_item(std::string name_, std::string description_, float weight_, int price_, int quantity_, std::string category_);
//
//        void save_to_file();
//
//
//};
//
//#endif