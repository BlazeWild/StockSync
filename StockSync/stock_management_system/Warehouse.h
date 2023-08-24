//#ifndef Warehouse_H
//#define Warehouse_H
//
//#pragma once
//#include <iostream>
//#include <string>
//#include <vector>
//#include "WarehouseItem.h"
//#include <filesystem>
//#include <fstream>
//#include "WarehouseItem.h"
//class Warehouse{
//    private:
//        // static int warehouse_count;
//        // int id;
//        std::string name;
//        // std::vector<Rack> racks;
//
//    public:
//        Warehouse(){};
//
//        // Warehouse(std::string name_, std::vector<Rack> racks_) : name(name_), racks(racks_){
//        //     // id = warehouse_count++;
//        // }
//    void add_item(std::string name_, std::string description_, float weight_, int price_, int quantity_, std::string category_);
//    void remove_item(long int id);
//    std::vector <WarehouseItem> get_all_items();
//
//    std::vector <std::string> get_all_item_files();
//
//
//
//    WarehouseItem read_item_file(long int id);
//
//    // int get_id();
//
//// TODO
//    std::vector <WarehouseItem> get_items_by_category();
//
//
//        // void add_rack(Rack rack);
//
//        // void remove_rack(Rack rack);
//        
//
//        // std::vector <Rack> get_racks();
//
//        // Rack get_rack_by_id(long int id);
//
//        ~Warehouse(){};
//
//    friend std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse);
//
//};
//
//#endif