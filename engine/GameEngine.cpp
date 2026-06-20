#include "../engine/GameEngine.h"
#include "../engine/CommandExecutor.h"
#include "../engine/Serializer.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

static const std::string SAVE_FILE = "savefile.txt";

GameEngine::GameEngine()
    : executor(std::make_unique<CommandExecutor>(*this)) {}

GameEngine::~GameEngine() = default;

UserService&   GameEngine::getUserService()   { return userService;   }
MarketService& GameEngine::getMarketService() { return marketService; }
TaskService&   GameEngine::getTaskService()   { return taskService;   }

Player* GameEngine::getCurrentPlayer() const {
    return userService.getCurrentPlayer();
}

void GameEngine::resetGame() {
    userService.clearAll();
    userService.resetNextId(1);
    marketService.reset();
    taskService.reset();
    std::cout << "Game reset successfully!\n";
}

void GameEngine::save() {
    std::ofstream out(SAVE_FILE);
    if (!out.is_open()) throw std::runtime_error("Could not open save file: " + SAVE_FILE);
    Serializer::serializeAll(out,
            userService.getPlayersOwned(),
            userService.getMarketManagerOwned(),
            userService.getTaskManagerOwned(),
            marketService.getMarket(),
            taskService.getTaskBoard());
}

void GameEngine::load() {
    std::ifstream in(SAVE_FILE);
    if (!in.is_open()) return;

    userService.clearAll();

    std::vector<std::unique_ptr<Player>> loadedPlayers;
    std::unique_ptr<MarketManager> loadedMarketManager;
    std::unique_ptr<TaskManager>   loadedTaskManager;
    int nextId = 1;

    Serializer::deserializeAll(in,
                                loadedPlayers,
                                loadedMarketManager,
                                loadedTaskManager,
                                marketService.getMarket(),
                                taskService.getTaskBoard(),
                                nextId);

    for (auto& p : loadedPlayers)
        userService.addPlayer(std::move(p));
    if (loadedMarketManager)
        userService.setMarketManager(std::move(loadedMarketManager));
    if (loadedTaskManager)
        userService.setTaskManager(std::move(loadedTaskManager));
    userService.resetNextId(nextId);
}

void GameEngine::run() {
    try {
        load();
    } catch (const std::exception& e) {
        std::cout << "Warning: Failed to load save: " << e.what() << "\n";
    }

    std::cout << "========================================\n";
    std::cout << "                BARN BOSS\n";
    std::cout << "========================================\n";

    std::string input;
    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, input)) break;
        if (input.empty()) continue;

        Command cmd = Command::parse(input);

        if (cmd.name == "exit") {
            try {
                save();
                std::cout << "Game saved successfully. Goodbye!\n";
            } catch (const std::exception& e) {
                std::cout << "Warning: " << e.what() << "\n";
            }
            break;
        }

        try {
            executor->execute(cmd);
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }
}
