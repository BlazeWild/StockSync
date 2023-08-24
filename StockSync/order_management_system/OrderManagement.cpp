#include "OrderManagement.h"
#include "Order.h"

// void OrderManagement::place_order() {
//     // order.set_order();
//     Order order;
//     order.set_order();
//     // order.push_back(order);
//     std::cout << "Order placed" << std::endl;
// }

void OrderManagement::place_order(std::string customer_name_, std::string product_name_, int quantity_, int rate_, int total_price_) {
    Order order;
    order.set_order(customer_name_, product_name_, quantity_, rate_, total_price_);
    std::cout << "Order placed" << std::endl;
}

// void OrderManagement::cancel_order(long int order_id) {
//     Order order = Order::read_order_file(order_id);
//     order.set_is_cancelled(true);
//     std::cout << "Order cancelled" << std::endl;
// }

// void OrderManagement::update_delivery_status(long int order_id) {
//     Order order = Order::read_order_file(order_id);
//     order.set_is_delivered(true);
//     std::cout << "Order status updated" << std::endl;
// }

// Order OrderManagement::read_order_file(long int order_id){
//     for (int i = 0; i < orders.size(); i++){
//         if (orders[i].get_order_id() == order_id){
//             return orders[i];
//         }
//     }
// }

Order OrderManagement::read_order_file(long int order_id) {
    std::cout << "reading order file ordermanagement  " << order_id << std::endl;
    return Order::read_order_file(order_id);
}

std::vector <std::string> OrderManagement::get_all_order_files() {
    std::vector <std::string> file_names;
    for (const auto& entry : std::filesystem::directory_iterator("./orders")) {
        file_names.push_back(entry.path().string());
        std::cout << entry.path().string() << std::endl;
    }
    return file_names;
}




std::ostream& operator<<(std::ostream& os, const OrderManagement& order_management) {

    std::cout << "printing order  in management " << std::endl;

    // os << order_management.orders[0];
    return os;
}