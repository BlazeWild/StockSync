#ifndef Item_h
#define Item_h

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

class Item {
protected:
    static long int item_count;
    long int item_id;
    std::string name;
    std::string description;
    float weight;
    int price;
    int quantity;
    std::string category;
    std::chrono::system_clock::time_point listed_date;
    std::chrono::system_clock::time_point expiration_date;

public:
    Item(){};
    Item(std::string name_, std::string description_, float weight_, int price_, int quantity_, std::string category_, std::chrono::system_clock::time_point expiration_date_);    

    void set_item();

    void set_item(std::string name_, std::string description_, float weight_, int price_, int quantity_, std::string category_);

    long int get_id();

    float get_weight();

    int get_price();

    int get_quantity();

    std::string get_category();

    std::chrono::system_clock::time_point get_listed_date();

    std::chrono::system_clock::time_point get_expiration_date();

    // TODO ADD GETTERS
    ~Item(){};

    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};


#endif