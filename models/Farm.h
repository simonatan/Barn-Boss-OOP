#pragma once

#include <vector>
#include "../models/Plant.h"
#include "../models/Animal.h"

class Farm {
 std::vector<Plant> plants;
 std::vector<Animal> animals;
 size_t plantCapacity;
 size_t animalCapacity;

public:
 Farm();

 bool addPlant(const Plant& plant);
 bool addAnimal(const Animal& animal);

 void expandPlantCapacity();
 void expandAnimalCapacity();

 void growAll();

 std::vector<Plant>& getPlants();
 std::vector<Animal>& getAnimals();

 [[nodiscard]] size_t getPlantCapacity() const;
 [[nodiscard]] size_t getAnimalCapacity() const;

 [[nodiscard]] size_t getPlantCount() const;
 [[nodiscard]] size_t getAnimalCount() const;
};