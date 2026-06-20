#include "../models/TaskManager.h"

bool TaskManager::exists = false;

TaskManager::TaskManager(int id_, const std::string& username_, const std::string& password_)
    : User(id_, username_, password_) { exists = true; }

std::string TaskManager::getType() const { return "TaskManager"; }
bool TaskManager::canCreate() { return !exists; }
void TaskManager::resetTracker() { exists = false; }
