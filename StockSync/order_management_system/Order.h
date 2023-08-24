#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include "../util.h"
#include <fstream>
#include <limits>


class Order {
private:
    static long int order_count;
    long int order_id;
    //TODO add functionality to use user object instead of name
    std::string customer_name;
    bool is_delivered;
    bool is_cancelled;
    std::chrono::system_clock::time_point order_date;
    std::chrono::system_clock::time_point delivery_date;
    std::string product_name;
    int quantity;
    int rate, total_price;
    friend class Admin;
    friend class ClientFrame;

public:
    Order() {};

    // void set_order();

    void set_order(std::string customer_name_, std::string product_name_, int quantity_, int rate, int total_price);

    long int get_order_id();

    std::string get_customer_name();

    bool get_is_delivered();

    bool get_is_cancelled();

    std::chrono::system_clock::time_point get_order_date();

    std::chrono::system_clock::time_point get_delivery_date();

    void set_is_delivered(bool b);

    void set_is_cancelled(bool b);

    void set_delivery_date();

    void save_to_file();

    static Order read_order_file(long int order_id);

    friend std::ostream& operator<<(std::ostream& os, const Order& order);

    ~Order() {};
};

#endif