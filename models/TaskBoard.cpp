#include "../models/TaskBoard.h"
#include "../utils/Exceptions.h"
#include <iostream>

TaskBoard::TaskBoard() : nextId(1) {
    addTask("Wheat", 5, 50, 10);
    addTask("Milk",  3, 120, 20);
}

Task* TaskBoard::findTask(int id) {
    for (auto& t : tasks)
        if (t.getId() == id)
            return &t;
    return nullptr;
}

void TaskBoard::showTasks() const {
    std::cout << "=== TASK BOARD ===\n";
    for (const auto& t : tasks)
        t.print();
}

void TaskBoard::addTask(const std::string& product, int quantity, int rewardBalance, int rewardScore) {
    tasks.emplace_back(nextId++, product, quantity, rewardBalance, rewardScore);
}

void TaskBoard::addTaskWithId(int id, const std::string& product, int quantity, int rewardBalance, int rewardScore) {
    tasks.emplace_back(id, product, quantity, rewardBalance, rewardScore);
    if (id >= nextId) nextId = id + 1;
}

void TaskBoard::removeTask(int id) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->getId() == id) {
            tasks.erase(it);
            return;
        }
    }
    throw NotFoundException("Task ID " + std::to_string(id));
}

bool TaskBoard::completeTask(int id, Player& player) {
    Task* task = findTask(id);
    if (!task) throw NotFoundException("Task ID " + std::to_string(id));

    player.removeItem(task->getProduct(), task->getQuantity());

    player.addBalance(task->getRewardBalance());
    player.addScore(task->getRewardScore());
    std::cout << "Task completed successfully!\n";

    removeTask(id);
    return true;
}

const std::vector<Task>& TaskBoard::getTasks() const { return tasks; }
void TaskBoard::clearTasks() { tasks.clear(); nextId = 1; }
