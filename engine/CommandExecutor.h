#pragma once

#include "../engine/Command.h"
#include "../models/User.h"

class GameEngine;

class CommandExecutor {
    GameEngine& engine;
    User* requirePlayer() const;

public:
    CommandExecutor(GameEngine& engine);
    void execute(const Command& cmd);
};
