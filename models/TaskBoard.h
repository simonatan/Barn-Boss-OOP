#pragma once

#include <vector>
#include "../models/Task.h"
#include "../models/Player.h"

class TaskBoard {
    std::vector<Task> tasks;
    int nextId;

public:
    TaskBoard();

    Task* findTask(int id);
    void showTasks() const;
    void addTask(const std::string& product, int quantity, int rewardBalance, int rewardScore);
    void addTaskWithId(int id, const std::string& product, int quantity, int rewardBalance, int rewardScore);
    void removeTask(int id);
    bool completeTask(int id, Player& player);

    [[nodiscard]] const std::vector<Task>& getTasks() const;
    void clearTasks();
};
