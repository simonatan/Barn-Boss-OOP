#include "../models/Market.h"
#include "../utils/Validator.h"
#include "../utils/Exceptions.h"
#include <iostream>

Market::Market() {
    products = {
        {1, "WheatSeed", 10, 20},
        {2, "CornSeed",  15, 20},
        {3, "Chicken",   25, 10},
        {4, "Cow",       50,  5},
        {5, "Wheat",     15, 20},
        {6, "Corn",      20, 20},
        {7, "Egg",       30, 15},
        {8, "Milk",      60, 10}
    };
}

Product& Market::findProduct(int id) {
    for (auto& p : products)
        if (p.id == id) return p;
    throw NotFoundException("Product ID " + std::to_string(id));
}

void Market::showCatalog() const {
    std::cout << "=== MARKET CATALOG ===\n";
    for (const auto& p : products)
        std::cout << p.id << ". " << p.name
                  << " | Qty: " << p.quantity
                  << " | Price: " << p.price << "\n";
}

bool Market::buyProduct(int id, int quantity, int& playerMoney, std::string& outItemName) {
    if (!Validator::isValidQuantity(quantity)) return false;
    Product& p = findProduct(id);
    if (p.quantity < quantity)
        throw NotEnoughItemsException(p.name + " in stock");
    int cost = p.price * quantity;
    if (playerMoney < cost)
        throw InsufficientFundsException(cost, playerMoney);

    p.quantity -= quantity;
    playerMoney -= cost;
    outItemName = p.name;
    std::cout << "The purchase was successful!\n";
    return true;
}

void Market::sellProduct(int id, int quantity) {
    if (!Validator::isValidQuantity(quantity)) return;
    Product& p = findProduct(id);
    p.quantity += quantity;
    std::cout << "The sale was successful!\n";
}

void Market::restock(int id, int quantity) {
    if (!Validator::isValidQuantity(quantity)) return;
    Product& p = findProduct(id);
    p.quantity += quantity;
    std::cout << "Product restocked successfully!\n";
}

void Market::changePrice(int id, int newPrice) {
    if (!Validator::isValidPrice(newPrice)) return;
    Product& p = findProduct(id);
    p.price = newPrice;
    std::cout << "Price changed successfully!\n";
}

const std::vector<Product>& Market::getProducts() const { return products; }
void Market::clearProducts() { products.clear(); }

void Market::setProduct(int id, const std::string& name, int price, int quantity) {
    for (auto& p : products) {
        if (p.id == id) { p.price = price; p.quantity = quantity; return; }
    }
    products.push_back({id, name, price, quantity});
}
