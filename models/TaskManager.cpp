#include "../models/TaskManager.h"

TaskManager::TaskManager(int id_, const std::string& username_, const std::string& password_)
    : User(id_, username_, password_) {}

std::string TaskManager::getType() const { return "TaskManager"; }
