#pragma once

#include <vector>
#include <string>
#include "../models/User.h"
#include "../models/Market.h"

class MarketService {
    Market market;

public:
    void openCatalog();
    bool buy(User* user, const std::vector<std::string>& args);
    bool sell(User* user, const std::vector<std::string>& args);
    void restock(User* user, const std::vector<std::string>& args);
    void changePrice(User* user, const std::vector<std::string>& args);
    Market& getMarket();
};
