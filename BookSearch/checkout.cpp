#include "checkout.h"
#include "cart.h"

#include <iostream>

Checkout::Checkout(std::map<int, CartItem> cart_items) {
    this->cart_items = cart_items;
}

void Checkout::process_order() {
    calculate_total_price();

    // Reset the cart to an empty dictionary
    cart_items.clear();
}

void Checkout::calculate_total_price() {
    total_price = 0;

    for (auto& item : cart_items) {
        total_price += item.second.price;
    }
}
