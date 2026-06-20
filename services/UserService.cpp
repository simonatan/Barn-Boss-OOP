#include "../services/UserService.h"
#include "../utils/Validator.h"
#include <iostream>

int UserService::nextId = 1;

UserService::UserService()
    : currentUser(nullptr), currentPlayer(nullptr),
      currentMarketManager(nullptr), currentTaskManager(nullptr) {}

void UserService::registerUser(const std::vector<std::string>& args) {
    if (!Validator::isValidCommandSize(args.size(), 3)) return;

    const std::string& username = args[0];
    const std::string& password = args[1];
    const std::string& type     = args[2];

    if (!Validator::isValidUsername(username) || !Validator::isValidPassword(password)) return;

    for (const auto& p : players)
        if (p->getUsername() == username) { std::cout << "Username already exists!\n"; return; }
    if (marketManager && marketManager->getUsername() == username)
        { std::cout << "Username already exists!\n"; return; }
    if (taskManager && taskManager->getUsername() == username)
        { std::cout << "Username already exists!\n"; return; }

    int newId = nextId++;

    if (type == "Player") {
        players.push_back(std::make_unique<Player>(newId, username, password));
    } else if (type == "MarketManager") {
        if (marketManager) { std::cout << "MarketManager already exists!\n"; return; }
        marketManager = std::make_unique<MarketManager>(newId, username, password);
    } else if (type == "TaskManager") {
        if (taskManager) { std::cout << "TaskManager already exists!\n"; return; }
        taskManager = std::make_unique<TaskManager>(newId, username, password);
    } else {
        std::cout << "Invalid user type!\n";
        return;
    }

    std::cout << "User registered successfully!\n";
}

void UserService::login(const std::vector<std::string>& args) {
    if (!Validator::isValidCommandSize(args.size(), 2)) return;
    if (currentUser) { std::cout << "Already logged in!\n"; return; }

    for (const auto& p : players) {
        if (p->getUsername() == args[0] && p->checkPassword(args[1])) {
            currentUser   = p.get();
            currentPlayer = p.get();
            std::cout << "Welcome, " << args[0] << "!\n";
            return;
        }
    }
    if (marketManager && marketManager->getUsername() == args[0] && marketManager->checkPassword(args[1])) {
        currentUser           = marketManager.get();
        currentMarketManager  = marketManager.get();
        std::cout << "Welcome, " << args[0] << "!\n";
        return;
    }
    if (taskManager && taskManager->getUsername() == args[0] && taskManager->checkPassword(args[1])) {
        currentUser         = taskManager.get();
        currentTaskManager  = taskManager.get();
        std::cout << "Welcome, " << args[0] << "!\n";
        return;
    }

    std::cout << "Invalid login!\n";
}

void UserService::logout() {
    if (!currentUser) { std::cout << "No user logged in!\n"; return; }
    currentUser          = nullptr;
    currentPlayer        = nullptr;
    currentMarketManager = nullptr;
    currentTaskManager   = nullptr;
    std::cout << "Logged out successfully!\n";
}

void UserService::changePassword(const std::vector<std::string>& args) const {
    if (!Validator::isValidCommandSize(args.size(), 2)) return;
    if (!currentUser) { std::cout << "Not logged in.\n"; return; }
    currentUser->changePassword(args[0], args[1]);
}

User*          UserService::getCurrentUser()          const { return currentUser; }
Player*        UserService::getCurrentPlayer()        const { return currentPlayer; }
MarketManager* UserService::getCurrentMarketManager() const { return currentMarketManager; }
TaskManager*   UserService::getCurrentTaskManager()   const { return currentTaskManager; }

std::vector<Player*> UserService::getPlayers() const {
    std::vector<Player*> result;
    result.reserve(players.size());
    for (const auto& p : players) result.push_back(p.get());
    return result;
}

void UserService::addPlayer(std::unique_ptr<Player> p) {
    players.push_back(std::move(p));
}

void UserService::setMarketManager(std::unique_ptr<MarketManager> m) {
    marketManager = std::move(m);
}

void UserService::setTaskManager(std::unique_ptr<TaskManager> t) {
    taskManager = std::move(t);
}

void UserService::clearAll() {
    players.clear();
    marketManager.reset();
    taskManager.reset();
    currentUser          = nullptr;
    currentPlayer        = nullptr;
    currentMarketManager = nullptr;
    currentTaskManager   = nullptr;
}

const std::vector<std::unique_ptr<Player>>& UserService::getPlayersOwned()        const { return players; }
const MarketManager*                         UserService::getMarketManagerOwned() const { return marketManager.get(); }
const TaskManager*                           UserService::getTaskManagerOwned()   const { return taskManager.get(); }

void UserService::resetNextId(int id) { nextId = id; }
