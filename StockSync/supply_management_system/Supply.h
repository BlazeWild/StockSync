#ifndef SUPPLY_H
#define SUPPLY_H

#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <fstream>
#include "../util.h"

class Supply {
private:
    static long int supply_count;
    long int supply_id;
    bool is_delivered;
    bool is_cancelled;
    bool is_accepted;
    // TODO: Add a supplier class
    std::string supplier_name;
    std::chrono::system_clock::time_point supply_date;
    std::chrono::system_clock::time_point delivery_date;
    // std::vector<SupplyItem> items;
    std::string product_name;
    int quantity;
    int price;
    std::string category;

    friend class Admin;
    friend class ClientFrame;

public:
    Supply(){};

    void set_supply();
    void set_supply(std::string supplier_name_, std::string name_,  int quantity_, int price_, std::string category_);
    void set_is_delivered(bool is_delivered_);
    void set_is_cancelled(bool is_cancelled_);
    void set_is_accepted(bool is_accepted_);

    // SupplyItem get_item();

    bool get_is_delivered();
    bool get_is_cancelled();
    bool get_is_accepted();
    void set_delivery_date();
    void set_delivery_date(std::chrono::system_clock::time_point date);
    std::chrono::system_clock::time_point get_delivery_date();
    std::chrono::system_clock::time_point get_supply_date();
    long int get_supply_id();
    void save_to_file();
    static Supply read_supply_file(long int supply_id);

    friend std::ostream& operator<<(std::ostream& os, const Supply& supply);

    ~Supply(){};

};

#endif