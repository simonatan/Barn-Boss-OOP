#pragma once

#include "../engine/Command.h"
#include "../models/Player.h"
#include "../models/MarketManager.h"
#include "../models/TaskManager.h"

class GameEngine;

class CommandExecutor {
    GameEngine& engine;
    void           requireLoggedIn() const;
    Player*        requirePlayer() const;
    MarketManager* requireMarketManager() const;
    TaskManager*   requireTaskManager() const;

public:
    CommandExecutor(GameEngine& engine);
    void execute(const Command& cmd);
};