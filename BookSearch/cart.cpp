#include "cart.h"

Cart::Cart()
{
    items = std::map<QString, CartItem>();
}

void Cart::add_item(const CartItem& item) {
    if (items.find(item.title) != items.end()) {
        items[item.title].quantity += 1;
    } else {
        items[item.title] = item;
        items[item.title].quantity = 1;
    }
}

void Cart::remove_item(const QString& title) {
    items.erase(title);
}

int Cart::get_item_count() {
    int count = 0;
    for (const auto& item : items) {
        count += item.second.quantity;
    }
    return count;
}

void Cart::clear_cart() {
    items.clear();
}

std::map<QString, CartItem> Cart::get_items() const {
    return items;
}
