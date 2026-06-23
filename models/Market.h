#pragma once

#include <vector>
#include "../models/Product.h"

class Market {
    std::vector<Product> products;

public:
    Market();

    void showCatalog() const;
    void buyProduct(int id, int quantity);
    void sellProduct(int id, int quantity);

    void restock(int id, int quantity);
    void changePrice(int id, int newPrice);

    Product& findProduct(int id);
    const std::vector<Product>& getProducts() const;
    void clearProducts();
    void setProduct(int id, const std::string& name, int price, int quantity);
};
