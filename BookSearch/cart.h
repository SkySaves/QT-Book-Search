#ifndef CART_H
#define CART_H

#include <map>
#include <string>

struct CartItem {
    std::string title;
    double price;
    int quantity;
};

class Cart {
public:
    Cart();
    void add_item(int book_id, std::string book_title, double price);
    void remove_item(int book_id);
    int get_item_count();
    void clear_cart();
    std::map<int, CartItem> get_items() const;

private:
    std::map<int, CartItem> items;
};

#endif // CART_H
