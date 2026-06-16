#include "ProductType.h"

std::string productToString(ProductType product) {
    switch (product) {
        case ProductType::Wheat: return "Wheat";
        case ProductType::Corn: return "Corn";
        case ProductType::Egg: return "Egg";
        case ProductType::Milk: return "Milk";
        case ProductType::WheatSeed: return "WheatSeed";
        case ProductType::CornSeed: return "CornSeed";
        case ProductType::Chicken: return "Chicken";
        case ProductType::Cow: return "Cow";
        default: return "Unknown";
    }
}

ProductType stringToProduct(const std::string &product) {
    if (product == "Wheat") return ProductType::Wheat;
    if (product == "Corn") return ProductType::Corn;
    if (product == "Egg") return ProductType::Egg;
    if (product == "Milk") return ProductType::Milk;
    if (product == "WheatSeed" || product == "Wheat Seed") return ProductType::WheatSeed;
    if (product == "CornSeed" || product == "Corn Seed") return ProductType::CornSeed;
    if (product == "Chicken") return ProductType::Chicken;
    if (product == "Cow") return ProductType::Cow;
    return ProductType::Unknown;
}
