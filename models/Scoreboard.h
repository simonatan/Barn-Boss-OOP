#pragma once

#include <vector>
#include "../models/User.h"

class Scoreboard {
public:
    static void showScoreboard(const std::vector<User*>& players);
};