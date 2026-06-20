#pragma once

#include <vector>
#include <string>
#include "../models/Player.h"
#include "../models/MarketManager.h"
#include "../models/Market.h"

class MarketService {
    Market market;

public:
    void openCatalog() const;
    bool buy(Player* player, const std::vector<std::string>& args);
    bool sell(Player* player, const std::vector<std::string>& args);
    void restock(MarketManager* manager, const std::vector<std::string>& args);
    void changePrice(MarketManager* manager, const std::vector<std::string>& args);
    Market& getMarket();
    void reset();
};
