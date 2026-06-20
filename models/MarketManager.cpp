#include "../models/MarketManager.h"

bool MarketManager::exists = false;

MarketManager::MarketManager(int id_, const std::string& username_, const std::string& password_)
    : User(id_, username_, password_) { exists = true; }

std::string MarketManager::getType() const { return "MarketManager"; }
bool MarketManager::canCreate() {
    return !exists;
}
void MarketManager::resetTracker() {
    exists = false;
}
