#pragma once

#include "../engine/Command.h"
#include "../models/Player.h"

class GameEngine;

class CommandExecutor {
    GameEngine& engine;
    Player* requirePlayer();

public:
    CommandExecutor(GameEngine& engine);
    void execute(const Command& cmd);
};
