#include "../utils/Validator.h"
#include <iostream>
#include <cctype>

bool Validator::isValidUsername(const std::string& username) {
    if (username.size() < 3) { std::cout << "Username too short!\n"; return false; }
    for (char c : username) {
        if (!std::isalnum(c) && c != '_') { std::cout << "Invalid username characters!\n"; return false; }
    }
    return true;
}

bool Validator::isValidPassword(const std::string& password) {
    if (password.size() < 3) { std::cout << "Password too short!\n"; return false; }
    return true;
}

bool Validator::isValidQuantity(int quantity) {
    if (quantity <= 0) { std::cout << "Quantity must be positive!\n"; return false; }
    return true;
}

bool Validator::isValidPrice(int price) {
    if (price <= 0) { std::cout << "Price must be positive!\n"; return false; }
    return true;
}

bool Validator::isValidCommandSize(std::size_t actual, std::size_t expected) {
    if (actual != expected) { std::cout << "Invalid command format!\n"; return false; }
    return true;
}
