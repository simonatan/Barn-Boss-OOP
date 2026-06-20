#pragma once

#include <vector>
#include <memory>
#include <fstream>
#include "../models/Player.h"
#include "../models/MarketManager.h"
#include "../models/TaskManager.h"
#include "../models/Market.h"
#include "../models/TaskBoard.h"

class Serializer {
public:
    static void serializeAll(std::ofstream& out,
                              const std::vector<std::unique_ptr<Player>>& players,
                              const MarketManager* marketManager,
                              const TaskManager* taskManager,
                              const Market& market,
                              const TaskBoard& taskBoard);

    static void deserializeAll(std::ifstream& in,
                                std::vector<std::unique_ptr<Player>>& players,
                                std::unique_ptr<MarketManager>& marketManager,
                                std::unique_ptr<TaskManager>& taskManager,
                                Market& market,
                                TaskBoard& taskBoard,
                                int& nextUserId);
};
