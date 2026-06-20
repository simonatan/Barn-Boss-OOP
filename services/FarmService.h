#pragma once

#include <vector>
#include <string>
#include "../models/User.h"

class FarmService {
public:
    FarmService() = default;
    static bool sowPlant(User* user, const std::vector<std::string>& args);
    static bool addAnimal(User* user, const std::vector<std::string>& args);
    static void harvest(User* user);
};
