#include "../services/FarmService.h"
#include "../utils/Exceptions.h"
#include "../utils/Utils.h"
#include "../models/Plant.h"
#include "../models/Animal.h"
#include <iostream>

bool FarmService::sowPlant(Player* player, const std::vector<std::string>& args) {
    if (!player) throw AuthenticationException("Not logged in!");
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

    if (!player->getBarn().hasItem(seedName, 1)) throw NotEnoughItemsException(seedName);

    Plant newPlant(seedId, plantOutput, requiredCycles, plantOutput);
    player->getFarm().addPlant(newPlant);
    player->removeItem(seedName, 1);

    std::cout << "Plants planted successfully!\n";
    return true;
}

bool FarmService::addAnimal(Player* player, const std::vector<std::string>& args) {
    if (!player) throw AuthenticationException("Not logged in!");
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

    if (!player->getBarn().hasItem(animalName, 1)) throw NotEnoughItemsException(animalName);

    Animal newAnimal(animalId, animalName, requiredCycles, animalOutput);
    player->getFarm().addAnimal(newAnimal);
    player->removeItem(animalName, 1);

    std::cout << "Animals added successfully!\n";
    return true;
}

void FarmService::harvest(Player* player) {
    if (!player) throw AuthenticationException("Not logged in!");

    Farm& farm = player->getFarm();

    auto& plants = farm.getPlants();
    for (int i = static_cast<int>(plants.size()) - 1; i >= 0; i--) {
        if (plants[i].isReady()) {
            player->addItem(plants[i].getOutput(), 1);
            farm.removePlant(i);
        }
    }

    auto& animals = farm.getAnimals();
    for (int i = static_cast<int>(animals.size()) - 1; i >= 0; i--) {
        if (animals[i].isReady()) {
            player->addItem(animals[i].getOutput(), 1);
            farm.removeAnimal(i);
        }
    }

    std::cout << "Harvest completed!\n";
}
