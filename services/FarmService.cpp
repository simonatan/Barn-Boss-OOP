#include "../services/FarmService.h"
#include "../models/User.h"
#include "../utils/Exceptions.h"
#include "../utils/Utils.h"
#include "../models/Plant.h"
#include "../models/Animal.h"
#include "Barn.h"
#include "Farm.h"
#include <iostream>

bool FarmService::sowPlant(User* user, const std::vector<std::string>& args) {
    if (!user) throw AuthenticationException("Not logged in!");
    if (args.empty()) throw InvalidCommandException("sowPlant needs a seed ID (1=Wheat, 2=Corn).");

    int seedId = Utils::toInt(args[0]);
    std::string seedName, plantOutput;
    int requiredCycles = 0;

    if (seedId == 1) {
        seedName = "WheatSeed";
        plantOutput = "Wheat";
        requiredCycles = 3;
    }
    else if (seedId == 2) {
        seedName = "CornSeed";
        plantOutput = "Corn";
        requiredCycles = 4;
    }
    else throw NotFoundException("Seed ID " + std::to_string(seedId));

    if (!user->getBarn().hasItem(seedName, 1)) throw NotEnoughItemsException(seedName);

    Plant newPlant(seedId, plantOutput, requiredCycles, plantOutput);
    user->getFarm().addPlant(newPlant);
    user->removeItem(seedName, 1);

    std::cout << "Plants planted successfully!\n";
    return true;
}

bool FarmService::addAnimal(User* user, const std::vector<std::string>& args) {
    if (!user) throw AuthenticationException("Not logged in!");
    if (args.empty()) throw InvalidCommandException("addAnimal needs an animal ID (3=Chicken, 4=Cow).");

    int animalId = Utils::toInt(args[0]);
    std::string animalName, animalOutput;
    int requiredCycles = 0;

    if (animalId == 3) {
        animalName = "Chicken";
        animalOutput = "Egg";
        requiredCycles = 3;
    }
    else if (animalId == 4) {
        animalName = "Cow";
        animalOutput = "Milk";
        requiredCycles = 5;
    }
    else throw NotFoundException("Animal ID " + std::to_string(animalId));

    if (!user->getBarn().hasItem(animalName, 1)) throw NotEnoughItemsException(animalName);

    Animal newAnimal(animalId, animalName, requiredCycles, animalOutput);
    user->getFarm().addAnimal(newAnimal);
    user->removeItem(animalName, 1);

    std::cout << "Animals added successfully!\n";
    return true;
}

void FarmService::harvest(User* user) {
    if (!user) throw AuthenticationException("Not logged in!");

    Farm& farm = user->getFarm();

    auto& plants = farm.getPlants();
    for (auto it = plants.begin(); it != plants.end(); ) {
        if (it->isReady()) {
            user->addItem(it->getOutput(), 1);
            it = plants.erase(it);
        } else {
            ++it;
        }
    }

    auto& animals = farm.getAnimals();
    for (auto it = animals.begin(); it != animals.end(); ) {
        if (it->isReady()) {
            user->addItem(it->getOutput(), 1);
            it = animals.erase(it);
        } else {
            ++it;
        }
    }

    std::cout << "Harvest completed!\n";
}
