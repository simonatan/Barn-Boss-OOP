#include "../engine/GameEngine.h"
#include "../engine/CommandExecutor.h"
#include "../models/Plant.h"
#include "../models/Animal.h"
#include "../utils/Utils.h"
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

Player* GameEngine::getCurrentPlayer() const { return userService.getCurrentPlayer(); }

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

    const auto& players = userService.getPlayersOwned();
    const auto* mm      = userService.getMarketManagerOwned();
    const auto* tm      = userService.getTaskManagerOwned();

    int maxId = 0;
    for (const auto& p : players) if (p->getId() > maxId) maxId = p->getId();
    if (mm && mm->getId() > maxId) maxId = mm->getId();
    if (tm && tm->getId() > maxId) maxId = tm->getId();
    out << "NEXT_ID " << (maxId + 1) << "\n";

    for (const auto& p : players) {
        out << "USER Player " << p->getId() << " " << p->getUsername()
            << " " << p->getPassword() << " " << p->getBalance()
            << " " << p->getScore() << " " << p->getCycle() << "\n";

        out << "BARN";
        for (const auto& kv : p->getBarn().getItems())
            out << " " << kv.first << " " << kv.second;
        out << "\n";

        out << "FARMCAP " << p->getFarm().getPlantCapacity()
            << " " << p->getFarm().getAnimalCapacity() << "\n";

        for (const auto& pl : p->getFarm().getPlants())
            out << "PLANT " << pl.getType() << " " << pl.getCurrentCycle()
                << " " << pl.getRequiredCycle() << " " << pl.getOutput() << "\n";

        for (const auto& an : p->getFarm().getAnimals())
            out << "ANIMAL " << an.getType() << " " << an.getCurrentCycle()
                << " " << an.getRequiredCycle() << " " << an.getOutput() << "\n";
    }

    if (mm) out << "USER MarketManager " << mm->getId() << " " << mm->getUsername() << " " << mm->getPassword() << "\n";
    if (tm) out << "USER TaskManager "   << tm->getId() << " " << tm->getUsername() << " " << tm->getPassword() << "\n";

    for (const auto& p : marketService.getMarket().getProducts())
        out << "MARKET " << p.id << " " << p.name << " " << p.price << " " << p.quantity << "\n";

    for (const auto& t : taskService.getTaskBoard().getTasks())
        out << "TASK " << t.getId() << " " << t.getProduct() << " "
            << t.getQuantity() << " " << t.getRewardBalance() << " " << t.getRewardScore() << "\n";
}

void GameEngine::load() {
    std::ifstream in(SAVE_FILE);
    if (!in.is_open()) return;

    userService.clearAll();
    Market&    market    = marketService.getMarket();
    TaskBoard& taskBoard = taskService.getTaskBoard();

    bool marketRestored    = false;
    bool taskBoardRestored = false;
    Player* currentPlayer  = nullptr;
    int nextId = 1;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::vector<std::string> w = Utils::splitWords(line);
        const std::string& tag = w[0];

        if (tag == "NEXT_ID") {
            nextId = Utils::asInt(w, 1, line);
        }
        else if (tag == "USER") {
            currentPlayer = nullptr;
            if (w[1] == "Player") {
                auto p = std::make_unique<Player>(Utils::asInt(w, 2, line), w[3], w[4]);
                p->setBalance(Utils::asInt(w, 5, line));
                p->addScore(Utils::asInt(w, 6, line));
                p->setCycle(Utils::asInt(w, 7, line));
                currentPlayer = p.get();
                userService.addPlayer(std::move(p));
            } else if (w[1] == "MarketManager") {
                userService.setMarketManager(std::make_unique<MarketManager>(Utils::asInt(w, 2, line), w[3], w[4]));
            } else if (w[1] == "TaskManager") {
                userService.setTaskManager(std::make_unique<TaskManager>(Utils::asInt(w, 2, line), w[3], w[4]));
            }
        }
        else if (tag == "BARN" && currentPlayer) {
            for (std::size_t i = 1; i + 1 < w.size(); i += 2)
                currentPlayer->addItem(w[i], Utils::asInt(w, i + 1, line));
        }
        else if (tag == "FARMCAP" && currentPlayer) {
            auto plantCap  = static_cast<std::size_t>(Utils::asInt(w, 1, line));
            auto animalCap = static_cast<std::size_t>(Utils::asInt(w, 2, line));
            while (currentPlayer->getFarm().getPlantCapacity()  < plantCap)  currentPlayer->getFarm().expandPlantCapacity();
            while (currentPlayer->getFarm().getAnimalCapacity() < animalCap) currentPlayer->getFarm().expandAnimalCapacity();
        }
        else if (tag == "PLANT" && currentPlayer) {
            Plant pl(0, w[1], Utils::asInt(w, 3, line), w[4]);
            pl.setCurrentCycle(Utils::asInt(w, 2, line));
            currentPlayer->getFarm().addPlant(pl);
        }
        else if (tag == "ANIMAL" && currentPlayer) {
            Animal an(0, w[1], Utils::asInt(w, 3, line), w[4]);
            an.setCurrentCycle(Utils::asInt(w, 2, line));
            currentPlayer->getFarm().addAnimal(an);
        }
        else if (tag == "MARKET") {
            if (!marketRestored) { market.clearProducts(); marketRestored = true; }
            market.setProduct(Utils::asInt(w, 1, line), w[2], Utils::asInt(w, 3, line), Utils::asInt(w, 4, line));
        }
        else if (tag == "TASK") {
            if (!taskBoardRestored) { taskBoard.clearTasks(); taskBoardRestored = true; }
            taskBoard.addTaskWithId(Utils::asInt(w, 1, line), w[2], Utils::asInt(w, 3, line), Utils::asInt(w, 4, line), Utils::asInt(w, 5, line));
        }
    }

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
