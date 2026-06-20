#pragma once

#include <vector>
#include <string>
#include "../models/Player.h"
#include "../models/TaskManager.h"
#include "../models/TaskBoard.h"

class TaskService {
    TaskBoard taskBoard;

public:
    void showTasks();
    void addTask(TaskManager* manager, const std::vector<std::string>& args);
    void removeTask(TaskManager* manager, const std::vector<std::string>& args);
    bool completeTask(Player* player, const std::vector<std::string>& args);
    TaskBoard& getTaskBoard();
    void reset();
};
