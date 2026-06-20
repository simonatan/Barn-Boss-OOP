#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../models/User.h"

class UserService {
    std::vector<std::unique_ptr<User>> users;
    User* currentUser;

public:
    UserService();

    void registerUser(const std::vector<std::string>& args);
    void login(const std::vector<std::string>& args);
    void logout();
    void changePassword(const std::vector<std::string>& args) const;

    [[nodiscard]] User* getCurrentUser() const;
    std::vector<std::unique_ptr<User>>& getUsersRef();
    [[nodiscard]] std::vector<User*> getAllUsers() const;
    void resetNextId(int id);
};
