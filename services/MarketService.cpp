#include "../services/MarketService.h"
#include "../models/Player.h"
#include "../utils/Utils.h"
#include "../utils/Validator.h"
#include "../utils/Exceptions.h"
#include <iostream>

void MarketService::openCatalog() { market.showCatalog(); }

bool MarketService::buy(User* user, const std::vector<std::string>& args) {
    if (!user || user->getType() != "Player")
        throw AuthenticationException("Only Players can purchase items!");
    if (!Validator::isValidCommandSize(args.size(), 2)) return false;

    auto* player  = dynamic_cast<Player*>(user); // dynamic cast !!
    int productId = Utils::toInt(args[0]);
    int quantity = Utils::toInt(args[1]);
    int balance = player->getBalance();
    std::string itemName;

    market.buyProduct(productId, quantity, balance, itemName);

    player->removeBalance(player->getBalance() - balance);
    player->addItem(itemName, quantity);
    return true;
}

bool MarketService::sell(User* user, const std::vector<std::string>& args) {
    if (!user || user->getType() != "Player")
        throw AuthenticationException("Only Players can sell items!");
    if (!Validator::isValidCommandSize(args.size(), 2)) return false;

    auto* player  = dynamic_cast<Player*>(user); // dynamic cast !!
    int productId = Utils::toInt(args[0]);
    int quantity  = Utils::toInt(args[1]);

    Product* p = market.findProduct(productId);
    if (!p) throw NotFoundException("Product ID " + std::to_string(productId));

    int income = p->price * quantity;
    player->removeItem(p->name, quantity);

    int dummy = 0;
    std::string itemName;
    market.sellProduct(productId, quantity, dummy, itemName); // dummy ??
    player->addBalance(income);
    return true;
}

void MarketService::restock(User* user, const std::vector<std::string>& args) {
    if (!user || user->getType() != "MarketManager")
        throw AuthenticationException("Only MarketManagers can restock!");
    if (!Validator::isValidCommandSize(args.size(), 2)) return;
    market.restock(Utils::toInt(args[0]), Utils::toInt(args[1]));
}

void MarketService::changePrice(User* user, const std::vector<std::string>& args) {
    if (!user || user->getType() != "MarketManager")
        throw AuthenticationException("Only MarketManagers can change prices!");
    if (!Validator::isValidCommandSize(args.size(), 2)) return;
    market.changePrice(Utils::toInt(args[0]), Utils::toInt(args[1]));
}

Market& MarketService::getMarket() { return market; }
