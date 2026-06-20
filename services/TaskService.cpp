#include "../services/TaskService.h"
#include "../utils/Exceptions.h"
#include "../utils/Utils.h"
#include "../utils/Validator.h"
#include <iostream>

void TaskService::showTasks() { taskBoard.showTasks(); }

void TaskService::addTask(TaskManager* manager, const std::vector<std::string>& args) {
    if (!manager) throw AuthenticationException("Only TaskManagers can add tasks!");
    if (!Validator::isValidCommandSize(args.size(), 4)) return;

    int qty = Utils::toInt(args[1]), rwdBal = Utils::toInt(args[2]), rwdScr = Utils::toInt(args[3]);
    if (!Validator::isValidQuantity(qty)) return;
    taskBoard.addTask(args[0], qty, rwdBal, rwdScr);
    std::cout << "Task added successfully!\n";
}

void TaskService::removeTask(TaskManager* manager, const std::vector<std::string>& args) {
    if (!manager) throw AuthenticationException("Only TaskManagers can remove tasks!");
    if (!Validator::isValidCommandSize(args.size(), 1)) return;
    taskBoard.removeTask(Utils::toInt(args[0])); // throws NotFoundException
    std::cout << "Task removed successfully!\n";
}

bool TaskService::completeTask(Player* player, const std::vector<std::string>& args) {
    if (!player) throw AuthenticationException("Not logged in as Player!");
    if (!Validator::isValidCommandSize(args.size(), 1)) return false;
    return taskBoard.completeTask(Utils::toInt(args[0]), *player);
}

TaskBoard& TaskService::getTaskBoard() { return taskBoard; }
void       TaskService::reset()        { taskBoard = TaskBoard(); }