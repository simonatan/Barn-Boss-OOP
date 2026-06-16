#pragma once

#include <vector>
#include "../models/Plant.h"
#include "../models/Animal.h"

class Farm {
 std::vector<Plant> plants;
 std::vector<Animal> animals;
 int plantCapacity;
 int animalCapacity;

public:
 Farm();

 bool addPlant(const Plant& plant);
 bool addAnimal(const Animal& animal);

 void expandPlantCapacity();
 void expandAnimalCapacity();

 void growAll();

 std::vector<Plant>& getPlants();
 std::vector<Animal>& getAnimals();

 void removePlant(int index);
 void removeAnimal(int index);

 int getPlantCapacity() const;
 int getAnimalCapacity() const;

 int getPlantCount() const;
 int getAnimalCount() const;
};