#pragma once

#include <vector>
#include "../models/Product.h"

class Market {
    std::vector<Product> products;

public:
    Market();

    void showCatalog() const;
    bool buyProduct(int id, int quantity, int& playerMoney, std::string& outItemName);
    bool sellProduct(int id, int quantity, int& playerMoney, std::string& outItemName);

    void restock(int id, int quantity);
    void changePrice(int id, int newPrice);

    Product& findProduct(int id);
    [[nodiscard]] const std::vector<Product>& getProducts() const;
    void clearProducts();
    void setProduct(int id, const std::string& name, int price, int quantity);
};
