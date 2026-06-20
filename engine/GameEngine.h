#pragma once

#include <memory>
#include "../services/UserService.h"
#include "../services/MarketService.h"
#include "../services/TaskService.h"

class CommandExecutor;

class GameEngine {
    UserService   userService;
    MarketService marketService;
    TaskService   taskService;
    std::unique_ptr<CommandExecutor> executor;

    void save();
    void load();

public:
    GameEngine();
    ~GameEngine();

    void run();
    void resetGame();

    UserService&   getUserService();
    MarketService& getMarketService();
    TaskService&   getTaskService();

    [[nodiscard]] Player* getCurrentPlayer() const;
};
