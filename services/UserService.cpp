#include "../services/UserService.h"
#include "../models/Player.h"
#include "../models/MarketManager.h"
#include "../models/TaskManager.h"
#include "../utils/IDGenerator.h"
#include "../utils/Validator.h"
#include "../utils/Exceptions.h"
#include <iostream>

UserService::UserService() : currentUser(nullptr) {}

void UserService::registerUser(const std::vector<std::string>& args) {
    if (!Validator::isValidCommandSize(args.size(), 3)) return;

    const std::string& username = args[0];
    const std::string& password = args[1];
    const std::string& type = args[2];

    if (!Validator::isValidUsername(username) || !Validator::isValidPassword(password)) return;

    for (const auto& u : users) {
        if (u->getUsername() == username) {
            std::cout << "Username already exists!\n";
            return;
        }
    }

    int newId = IDGenerator::generateId();
    std::unique_ptr<User> newUser;

    if (type == "Player") {
        newUser = std::make_unique<Player>(newId, username, password);
    } else if (type == "MarketManager") {
        if (!MarketManager::canCreate()) { std::cout << "MarketManager already exists!\n"; return; }
        newUser = std::make_unique<MarketManager>(newId, username, password);
    } else if (type == "TaskManager") {
        if (!TaskManager::canCreate()) { std::cout << "TaskManager already exists!\n"; return; }
        newUser = std::make_unique<TaskManager>(newId, username, password);
    } else {
        std::cout << "Invalid user type!\n";
        return;
    }

    users.push_back(std::move(newUser));
    std::cout << "User registered successfully!\n";
}

void UserService::login(const std::vector<std::string>& args) {
    if (!Validator::isValidCommandSize(args.size(), 2)) return;
    if (currentUser) { std::cout << "Already logged in!\n"; return; }

    for (const auto& u : users) {
        if (u->getUsername() == args[0] && u->checkPassword(args[1])) {
            currentUser = u.get();
            std::cout << "Welcome, " << args[0] << "!\n";
            return;
        }
    }
    std::cout << "Invalid login!\n";
}

void UserService::logout() {
    if (!currentUser) { std::cout << "No user logged in!\n"; return; }
    currentUser = nullptr;
    std::cout << "Logged out successfully!\n";
}

void UserService::changePassword(const std::vector<std::string>& args) const {
    if (!Validator::isValidCommandSize(args.size(), 2)) return;
    if (!currentUser) { std::cout << "Not logged in.\n"; return; }
    currentUser->changePassword(args[0], args[1]);
}

User* UserService::getCurrentUser() const { return currentUser; }

std::vector<std::unique_ptr<User>>& UserService::getUsersRef() { return users; }

std::vector<User*> UserService::getAllUsers() const {
    std::vector<User*> raw;
    raw.reserve(users.size());
    for (const auto& u : users) raw.push_back(u.get());
    return raw;
}

void UserService::resetNextId(int id) {
    IDGenerator::reset();
    for (int i = 1; i < id; i++) IDGenerator::generateId();
}
