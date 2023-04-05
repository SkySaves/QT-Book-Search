#include "cart.h"



Cart::Cart()
{
    items = std::map<int, CartItem>();
}

void Cart::add_item(int book_id, std::string book_title, double price) {
    if (items.find(book_id) != items.end()) {
        items[book_id].quantity += 1;
    } else {
        CartItem item = {book_title, price, 1};
        items[book_id] = item;
    }
}

void Cart::remove_item(int book_id) {
    items.erase(book_id);
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

std::map<int, CartItem> Cart::get_items() const {
    return items;
}
