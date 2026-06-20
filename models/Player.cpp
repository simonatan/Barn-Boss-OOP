#include "../models/Player.h"
#include "../utils/Exceptions.h"
#include "../models/Barn.h"
#include "../models/Farm.h"
#include "../models/Plant.h"
#include "../models/Animal.h"
#include <iostream>

Player::Player(int id_, const std::string& username_, const std::string& password_)
    : User(id_, username_, password_), balance(100), score(0), cycle(0) {}

std::string Player::getType() const { return "Player"; }
int Player::getBalance() const { return balance;  }
int Player::getScore() const { return score; }
int Player::getCycle() const { return cycle; }

void Player::setBalance(int amount) { balance = amount; }
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
    int cap = static_cast<int>(farm.getPlantCapacity());
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
    int cap = static_cast<int>(farm.getAnimalCapacity());
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

bool Player::sowPlant(int seedId) {
    std::string seedName, plantOutput;
    int requiredCycles;
    if      (seedId == 1) { seedName = "WheatSeed"; plantOutput = "Wheat"; requiredCycles = 3; }
    else if (seedId == 2) { seedName = "CornSeed";  plantOutput = "Corn";  requiredCycles = 4; }
    else throw NotFoundException("Seed ID " + std::to_string(seedId));

    if (!barn.hasItem(seedName, 1)) throw NotEnoughItemsException(seedName);
    farm.addPlant(Plant(seedId, plantOutput, requiredCycles, plantOutput));
    barn.removeItem(seedName, 1);
    std::cout << "Plants planted successfully!\n";
    return true;
}

bool Player::addAnimal(int animalId) {
    std::string animalName, animalOutput;
    int requiredCycles;
    if      (animalId == 3) { animalName = "Chicken"; animalOutput = "Egg";  requiredCycles = 3; }
    else if (animalId == 4) { animalName = "Cow";     animalOutput = "Milk"; requiredCycles = 5; }
    else throw NotFoundException("Animal ID " + std::to_string(animalId));

    if (!barn.hasItem(animalName, 1)) throw NotEnoughItemsException(animalName);
    farm.addAnimal(Animal(animalId, animalName, requiredCycles, animalOutput));
    barn.removeItem(animalName, 1);
    std::cout << "Animals added successfully!\n";
    return true;
}

void Player::harvest() {
    auto& plants = farm.getPlants();
    for (auto it = plants.begin(); it != plants.end(); ) {
        if (it->isReady()) { barn.addItem(it->getOutput(), 1); it = plants.erase(it); }
        else ++it;
    }
    auto& animals = farm.getAnimals();
    for (auto it = animals.begin(); it != animals.end(); ) {
        if (it->isReady()) { barn.addItem(it->getOutput(), 1); it = animals.erase(it); }
        else ++it;
    }
    std::cout << "Harvest completed!\n";
}
