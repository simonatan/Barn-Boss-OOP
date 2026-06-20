#pragma once

#include <vector>
#include <string>
#include "../models/Player.h"
#include "../models/User.h"
#include "../models/TaskBoard.h"

class TaskService {
    TaskBoard taskBoard;

public:
    void showTasks();
    void addTask(User* user, const std::vector<std::string>& args);
    void removeTask(User* user, const std::vector<std::string>& args);
    bool completeTask(Player* player, const std::vector<std::string>& args);
    TaskBoard& getTaskBoard();
};
