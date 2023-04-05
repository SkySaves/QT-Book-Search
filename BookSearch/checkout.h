#ifndef CHECKOUT_H
#define CHECKOUT_H


#include "cart.h"
#include <map>
#include <string>

class Checkout {
public:
    Checkout(std::map<int, CartItem> cart_items);

    void process_order();
    double total_price;

private:
    std::map<int, CartItem> cart_items;

    void calculate_total_price();
};

#endif // CHECKOUT_H
