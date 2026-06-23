#include "../models/Farm.h"
#include "../utils/Exceptions.h"

Farm::Farm() : plantCapacity(3), animalCapacity(3) {}

bool Farm::addPlant(const Plant& plant) {
    if (plants.size() >= plantCapacity)
        throw CapacityFullException("plant: Cropland is full.");
    plants.push_back(plant);
    return true;
}

bool Farm::addAnimal(const Animal& animal) {
    if (animals.size() >= animalCapacity)
        throw CapacityFullException("add animal: Farmland is full.");
    animals.push_back(animal);
    return true;
}

void Farm::expandPlantCapacity()  { plantCapacity++;  }
void Farm::expandAnimalCapacity() { animalCapacity++; }
void Farm::setPlantCapacity(std::size_t cap)  { plantCapacity  = cap; }
void Farm::setAnimalCapacity(std::size_t cap) { animalCapacity = cap; }

void Farm::growAll() {
    for (auto& p : plants) p.grow();
    for (auto& a : animals) a.grow();
}

std::vector<Plant>&  Farm::getPlants()  { return plants;  }
std::vector<Animal>& Farm::getAnimals() { return animals; }

size_t Farm::getPlantCapacity() const {
    return plantCapacity;
}
size_t Farm::getAnimalCapacity() const {
    return animalCapacity;
}
size_t Farm::getPlantCount() const {
    return plants.size();
}
size_t Farm::getAnimalCount() const {
    return animals.size();
}
