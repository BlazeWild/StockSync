#ifndef SUPPLYMANAGEMENT_H
#define SUPPLYMANAGEMENT_H

#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include "../util.h"
#include <filesystem>
#include <fstream>
#include "Supply.h"

// TODO read all the files in the supplies folder and add them to the vector to read all

// FIXME MAKE A SUPPLY CLASS AND USE THIS CLASS TO MANAGE SUPPLIES
class SupplyManagement {
private:
    // std::vector <Supply> supplies;

public:
    SupplyManagement(){};

    void offer_supply();

    void offer_supply(std::string supplier_name_, std::string name_,  int quantity_, int price_, std::string category_);

    static Supply read_supply_file(long int supply_id);

    std::vector <std::string> get_all_supply_files();

    void cancel_supply(long int supply_id);

    void update_delivery_status(long int supply_id);

    void accept_supply(long int supply_id);

    ~SupplyManagement(){};

    friend std::ostream& operator<<(std::ostream& os, const SupplyManagement& supply);
};
#endif