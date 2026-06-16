#pragma once

#include <string>

enum class ProductType {
    Wheat,
    Corn,
    Egg,
    Milk,
    WheatSeed,
    CornSeed,
    Chicken,
    Cow,
    Unknown
};

std::string productToString(ProductType product);
ProductType stringToProduct(const std::string& product);
