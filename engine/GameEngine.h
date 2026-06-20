#pragma once

#include <memory>
#include "../models/Player.h"
#include "../services/UserService.h"
#include "../services/MarketService.h"
#include "../services/FarmService.h"
#include "../services/TaskService.h"

class CommandExecutor;

class GameEngine {
    UserService   userService;
    MarketService marketService;
    FarmService   farmService;
    TaskService   taskService;
    std::unique_ptr<CommandExecutor> executor;

    void save();
    void load();

public:
    GameEngine();
    ~GameEngine();

    void run();

    UserService&   getUserService();
    MarketService& getMarketService();
    FarmService&   getFarmService();
    TaskService&   getTaskService();

    Player* getCurrentPlayer();
};
