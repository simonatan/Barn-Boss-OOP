#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../models/Player.h"
#include "../models/MarketManager.h"
#include "../models/TaskManager.h"

class UserService {
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<MarketManager> marketManager;
    std::unique_ptr<TaskManager>   taskManager;

    User*          currentUser;
    Player*        currentPlayer;
    MarketManager* currentMarketManager;
    TaskManager*   currentTaskManager;

public:
    UserService();

    void registerUser(const std::vector<std::string>& args);
    void login(const std::vector<std::string>& args);
    void logout();
    void changePassword(const std::vector<std::string>& args) const;

    User*          getCurrentUser()          const;
    Player*        getCurrentPlayer()        const;
    MarketManager* getCurrentMarketManager() const;
    TaskManager*   getCurrentTaskManager()   const;

    std::vector<Player*> getPlayers() const;
    std::vector<User*>   getAllUsers() const;

    // For deserialization
    void addPlayer(std::unique_ptr<Player> p);
    void setMarketManager(std::unique_ptr<MarketManager> m);
    void setTaskManager(std::unique_ptr<TaskManager> t);
    void clearAll();

    const std::vector<std::unique_ptr<Player>>& getPlayersOwned()        const;
    const MarketManager*                         getMarketManagerOwned() const;
    const TaskManager*                           getTaskManagerOwned()   const;

    void resetNextId(int id);
};
