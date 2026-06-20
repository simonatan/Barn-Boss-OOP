#pragma once

#include <vector>
#include "../models/Player.h"

class Scoreboard {
public:
    static void showScoreboard(const std::vector<Player*>& players);
};
