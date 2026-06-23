#include "../services/MarketService.h"
#include "../utils/Utils.h"
#include "../utils/Validator.h"
#include "../utils/Exceptions.h"
#include <iostream>

void MarketService::openCatalog() const { market.showCatalog(); }

bool MarketService::buy(Player* player, const std::vector<std::string>& args) {
    if (!player) throw AuthenticationException("Only Players can purchase items!");
    if (!Validator::isValidCommandSize(args.size(), 2)) return false;

    int productId = Utils::toInt(args[0]);
    int quantity  = Utils::toInt(args[1]);
    if (!Validator::isValidQuantity(quantity)) return false;

    Product& p = market.findProduct(productId);
    int cost = p.price * quantity;
    if (player->getBalance() < cost) throw InsufficientFundsException(cost, player->getBalance());

    market.buyProduct(productId, quantity);
    player->removeBalance(cost);
    player->addItem(p.name, quantity);
    return true;
}

bool MarketService::sell(Player* player, const std::vector<std::string>& args) {
    if (!player) throw AuthenticationException("Only Players can sell items!");
    if (!Validator::isValidCommandSize(args.size(), 2)) return false;

    int productId = Utils::toInt(args[0]);
    int quantity  = Utils::toInt(args[1]);

    Product& p = market.findProduct(productId);
    player->removeItem(p.name, quantity);
    market.sellProduct(productId, quantity);
    player->addBalance(p.price * quantity);
    return true;
}

void MarketService::restock(MarketManager* manager, const std::vector<std::string>& args) {
    if (!manager) throw AuthenticationException("Only MarketManagers can restock!");
    if (!Validator::isValidCommandSize(args.size(), 2)) return;
    market.restock(Utils::toInt(args[0]), Utils::toInt(args[1]));
}

void MarketService::changePrice(MarketManager* manager, const std::vector<std::string>& args) {
    if (!manager) throw AuthenticationException("Only MarketManagers can change prices!");
    if (!Validator::isValidCommandSize(args.size(), 2)) return;
    market.changePrice(Utils::toInt(args[0]), Utils::toInt(args[1]));
}

Market& MarketService::getMarket() { return market; }
void    MarketService::reset()     { market = Market(); }