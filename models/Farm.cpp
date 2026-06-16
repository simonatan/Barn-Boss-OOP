#include "../models/Farm.h"
#include "../utils/Exceptions.h"

Farm::Farm() : plantCapacity(3), animalCapacity(3) {}

bool Farm::addPlant(const Plant& plant) {
    if (static_cast<int>(plants.size()) >= plantCapacity)
        throw CapacityFullException("Cropland is full.");
    plants.push_back(plant);
    return true;
}

bool Farm::addAnimal(const Animal& animal) {
    if (static_cast<int>(animals.size()) >= animalCapacity)
        throw CapacityFullException("Farmland is full.");
    animals.push_back(animal);
    return true;
}

void Farm::expandPlantCapacity() {
    plantCapacity++;
}
void Farm::expandAnimalCapacity() {
    animalCapacity++;
}

void Farm::growAll() {
    for (auto& p : plants) p.grow();
    for (auto& a : animals) a.grow();
}

std::vector<Plant>&  Farm::getPlants()  { return plants;  }
std::vector<Animal>& Farm::getAnimals() { return animals; }

void Farm::removePlant(int index) {
    if (index >= 0 && index < static_cast<int>(plants.size()))
        plants.erase(plants.begin() + index);
}

void Farm::removeAnimal(int index) {
    if (index >= 0 && index < static_cast<int>(animals.size()))
        animals.erase(animals.begin() + index);
}

int Farm::getPlantCapacity() const {
    return plantCapacity;
}
int Farm::getAnimalCapacity() const {
    return animalCapacity;
}
int Farm::getPlantCount() const {
    return static_cast<int>(plants.size());
}
int Farm::getAnimalCount() const {
    return static_cast<int>(animals.size());
}
