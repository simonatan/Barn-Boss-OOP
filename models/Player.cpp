#include "../models/Player.h"
#include "../utils/Exceptions.h"
#include <iostream>

Player::Player(int id_, const std::string& username_, const std::string& password_)
    : User(id_, username_, password_), balance(100), score(0), cycle(0) {}

std::string Player::getType() const { return "Player"; }
int Player::getBalance() const { return balance;  }
int Player::getScore() const { return score; }
int Player::getCycle() const { return cycle; }

void Player::addBalance(int amount) { balance += amount; }
void Player::removeBalance(int amount) { balance -= amount; }
void Player::addScore(int amount) { score += amount; }
void Player::setCycle(int c) { cycle = c; }

void Player::advanceCycle() {
    cycle++;
    farm.growAll();
}

void Player::profileInfo() const {
    User::profileInfo();
    std::cout << "Balance: " << balance << "\n";
    std::cout << "Score: "   << score   << "\n";
}

void  Player::addItem(const std::string& item, int qty) { barn.addItem(item, qty); }
bool  Player::removeItem(const std::string& item, int qty) { return barn.removeItem(item, qty); }
int   Player::getItemQty(const std::string& item) const { return barn.getQuantity(item); }
void  Player::printBarn() const { barn.print(); }
Barn& Player::getBarn() { return barn; }

Farm& Player::getFarm() { return farm; }

void Player::checkFarm() const {
    std::cout << "=== FARM STATUS ===\n";
    std::cout << "Cropland: " << farm.getPlantCount()  << " / " << farm.getPlantCapacity()
              << " slots filled. (Free: " << (farm.getPlantCapacity()  - farm.getPlantCount())  << ")\n";
    std::cout << "Farmland: " << farm.getAnimalCount() << " / " << farm.getAnimalCapacity()
              << " slots filled. (Free: " << (farm.getAnimalCapacity() - farm.getAnimalCount()) << ")\n";
}

void Player::expandCropland() {
    int cap = farm.getPlantCapacity();
    int cost = 50 * cap;
    int requiredScore = cap * 10;

    if (score < requiredScore)
        throw GameException("Not enough Score! Required: " + std::to_string(requiredScore)
                            + ", Current: " + std::to_string(score));
    if (balance < cost)
        throw InsufficientFundsException(cost, balance);

    balance -= cost;
    farm.expandPlantCapacity();
    std::cout << "Cropland expanded successfully! New capacity: " << farm.getPlantCapacity() << "\n";
}

void Player::expandFarmland() {
    int cap = farm.getAnimalCapacity();
    int cost = 50 * cap;
    int requiredScore = cap * 10;

    if (score < requiredScore)
        throw GameException("Not enough Score! Required: " + std::to_string(requiredScore)
                            + ", Current: " + std::to_string(score));
    if (balance < cost)
        throw InsufficientFundsException(cost, balance);

    balance -= cost;
    farm.expandAnimalCapacity();
    std::cout << "Farmland expanded successfully! New capacity: " << farm.getAnimalCapacity() << "\n";
}
