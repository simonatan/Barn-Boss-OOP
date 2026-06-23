#pragma once

#include <vector>
#include "../models/Plant.h"
#include "../models/Animal.h"

class Farm {
 std::vector<Plant> plants;
 std::vector<Animal> animals;
 std::size_t plantCapacity;
 std::size_t animalCapacity;

public:
 Farm();

 bool addPlant(const Plant& plant);
 bool addAnimal(const Animal& animal);

 void expandPlantCapacity();
 void expandAnimalCapacity();
 void setPlantCapacity(std::size_t cap);
 void setAnimalCapacity(std::size_t cap);

 void growAll();

 std::vector<Plant>& getPlants();
 std::vector<Animal>& getAnimals();

 std::size_t getPlantCapacity() const;
 std::size_t getAnimalCapacity() const;

 std::size_t getPlantCount() const;
 std::size_t getAnimalCount() const;
};