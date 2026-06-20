#include "../models/MarketManager.h"

MarketManager::MarketManager(int id_, const std::string& username_, const std::string& password_)
    : User(id_, username_, password_) {}

std::string MarketManager::getType() const { return "MarketManager"; }
