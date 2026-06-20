#pragma once

#include <map>
#include <string>

class Barn {
    std::map<std::string, int> items;

public:
    Barn();

    void addItem(const std::string& item, int quantity);
    bool removeItem(const std::string& item, int quantity);
    int  getQuantity(const std::string& item) const;
    bool hasItem(const std::string& item, int quantity) const;
    const std::map<std::string, int>& getItems() const;

    void print() const;
};
