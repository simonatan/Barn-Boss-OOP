#pragma once

#include <string>
#include <cstddef>

class Validator {
public:
    static bool isValidUsername(const std::string& username);
    static bool isValidPassword(const std::string& password);
    static bool isValidQuantity(int quantity);
    static bool isValidPrice(int price);
    static bool isValidCommandSize(std::size_t actual, std::size_t expected);
};