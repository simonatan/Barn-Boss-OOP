#pragma once

#include "../models/User.h"

class TaskManager : public User {
public:
    TaskManager(int id, const std::string& username, const std::string& password);
    [[nodiscard]] std::string getType() const override;
};
