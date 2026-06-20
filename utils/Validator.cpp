#include "../utils/Validator.h"
#include <iostream>
#include <cctype>

void Validator::printError(const std::string& message) {
    std::cout << message << "\n";
}

bool Validator::isValidUsername(const std::string& username) {
    if (username.size() < 3) { printError("Username too short!"); return false; }
    for (char c : username) {
        if (!std::isalnum(c) && c != '_') { printError("Invalid username characters!"); return false; }
    }
    return true;
}

bool Validator::isValidPassword(const std::string& password) {
    if (password.size() < 3) { printError("Password too short!"); return false; }
    return true;
}

bool Validator::isValidQuantity(int quantity) {
    if (quantity <= 0) { printError("Quantity must be positive!"); return false; }
    return true;
}

bool Validator::isValidPrice(int price) {
    if (price <= 0) { printError("Price must be positive!"); return false; }
    return true;
}

bool Validator::isValidCommandSize(std::size_t actual, std::size_t expected) {
    if (actual != expected) { printError("Invalid command format!"); return false; }
    return true;
}
