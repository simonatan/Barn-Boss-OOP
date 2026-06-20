#include "../models/Barn.h"
#include "../utils/Exceptions.h"
#include <iostream>

Barn::Barn() = default;

void Barn::addItem(const std::string& item, int quantity) {
    if (quantity <= 0)
        throw NegativeQuantityException("add Item");
    items[item] += quantity;
}

bool Barn::removeItem(const std::string& item, int quantity) {
    if (quantity <= 0) return false;
    auto it = items.find(item);
    if (it == items.end() || it->second < quantity)
        throw NotEnoughItemsException(item);
    it->second -= quantity;
    if (it->second == 0) items.erase(it);
    return true;
}

int Barn::getQuantity(const std::string& item) const {
    auto it = items.find(item);
    return (it == items.end()) ? 0 : it->second;
}

bool Barn::hasItem(const std::string& item, int quantity) const {
    return getQuantity(item) >= quantity;
}

const std::map<std::string, int>& Barn::getItems() const {
    return items;
}

void Barn::print() const {
    std::cout << "=== BARN ===\n";
    const std::string order[] = {"WheatSeed","CornSeed","Chicken","Cow","Wheat","Corn","Egg","Milk"};
    for (const auto& name : order)
        std::cout << name << ": " << getQuantity(name) << "\n";
}

void Barn::clear() {
    items.clear();
}
