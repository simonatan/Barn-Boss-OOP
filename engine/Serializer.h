#pragma once

#include <vector>
#include <memory>
#include <fstream>
#include "../models/User.h"
#include "../models/Market.h"
#include "../models/TaskBoard.h"

class Serializer {
public:
    static void serializeAll(std::ofstream& out,
                              const std::vector<User*>& users,
                              const Market& market,
                              const TaskBoard& taskBoard);

    static void deserializeAll(std::ifstream& in,
                                std::vector<std::unique_ptr<User>>& users,
                                Market& market,
                                TaskBoard& taskBoard,
                                int& nextUserId);
};
