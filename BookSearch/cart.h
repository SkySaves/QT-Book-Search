#ifndef CART_H
#define CART_H

#include <map>
#include <string>
#include <QString>

struct CartItem {
    QString title;
    double price;
    int quantity;
};

class Cart {
public:
    Cart();
    void add_item(const CartItem& item);
    void remove_item(const QString& title);
    int get_item_count();
    void clear_cart();
    std::map<QString, CartItem> get_items() const;

private:
    std::map<QString, CartItem> items;
};

#endif // CART_H
