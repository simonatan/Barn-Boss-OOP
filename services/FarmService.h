#pragma once

#include <vector>
#include <string>
#include "../models/Player.h"

class FarmService {
public:
    FarmService() = default;
    static bool sowPlant(Player* player, const std::vector<std::string>& args);
    static bool addAnimal(Player* player, const std::vector<std::string>& args);
    static void harvest(Player* player);
};
