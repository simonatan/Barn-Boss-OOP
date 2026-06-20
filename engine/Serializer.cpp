#include "../engine/Serializer.h"
#include "../models/MarketManager.h"
#include "../models/TaskManager.h"
#include "../utils/Utils.h"
#include <stdexcept>

void Serializer::serializeAll(std::ofstream& out,
                               const std::vector<User*>& users,
                               const Market& market,
                               const TaskBoard& taskBoard) {

    int maxId = 0;
    for (auto* u : users) if (u->getId() > maxId) maxId = u->getId();
    out << "NEXT_ID " << (maxId + 1) << "\n";

    for (auto* u : users) {
        if (u->getType() == "Player") {
            out << "USER Player " << u->getId() << " " << u->getUsername()
                << " " << u->getPassword() << " " << u->getBalance()
                << " " << u->getScore() << " " << u->getCycle() << "\n";

            out << "BARN";
            for (const auto& kv : u->getBarn().getItems())
                out << " " << kv.first << " " << kv.second;
            out << "\n";

            out << "FARMCAP " << u->getFarm().getPlantCapacity()
                << " "        << u->getFarm().getAnimalCapacity() << "\n";

            for (const auto& pl : u->getFarm().getPlants())
                out << "PLANT " << pl.getType() << " " << pl.getCurrentCycle()
                    << " " << pl.getRequiredCycle() << " " << pl.getOutput() << "\n";

            for (const auto& an : u->getFarm().getAnimals())
                out << "ANIMAL " << an.getType() << " " << an.getCurrentCycle()
                    << " " << an.getRequiredCycle() << " " << an.getOutput() << "\n";
        } else if (u->getType() == "MarketManager") {
            out << "USER MarketManager " << u->getId() << " " << u->getUsername() << " " << u->getPassword() << "\n";
        } else if (u->getType() == "TaskManager") {
            out << "USER TaskManager "   << u->getId() << " " << u->getUsername() << " " << u->getPassword() << "\n";
        }
    }

    for (const auto& p : market.getProducts())
        out << "MARKET " << p.id << " " << p.name << " " << p.price << " " << p.quantity << "\n";

    for (const auto& t : taskBoard.getTasks())
        out << "TASK " << t.getId() << " " << t.getProduct() << " "
            << t.getQuantity() << " " << t.getRewardBalance() << " " << t.getRewardScore() << "\n";
}

void Serializer::deserializeAll(std::ifstream& in,
                                 std::vector<std::unique_ptr<User>>& users,
                                 Market& market,
                                 TaskBoard& taskBoard,
                                 int& nextUserId) {
    users.clear();
    market.clearProducts();
    taskBoard.clearTasks();
    MarketManager::resetTracker();
    TaskManager::resetTracker();

    Player* currentPlayer = nullptr;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::vector<std::string> w = Utils::splitWords(line);
        const std::string& tag = w[0];

        if (tag == "NEXT_ID") {
            nextUserId = Utils::asInt(w, 1, line);
        }
        else if (tag == "USER") {
            currentPlayer = nullptr;
            const std::string& type = w[1];
            if (type == "Player") {
                int id           = Utils::asInt(w, 2, line);
                std::string username = w[3];
                std::string password = w[4];
                int balance      = Utils::asInt(w, 5, line);
                int score        = Utils::asInt(w, 6, line);
                int cycle        = Utils::asInt(w, 7, line);

                auto p = std::make_unique<Player>(id, username, password);
                p->addBalance(balance - 100);
                p->addScore(score);
                p->setCycle(cycle);
                currentPlayer = p.get();
                users.push_back(std::move(p));
            } else if (type == "MarketManager") {
                int id = Utils::asInt(w, 2, line);
                std::string username = w[3];
                std::string password = w[4];
                users.push_back(std::make_unique<MarketManager>(id, username, password));
            } else if (type == "TaskManager") {
                int id = Utils::asInt(w, 2, line);
                std::string username = w[3];
                std::string password = w[4];
                users.push_back(std::make_unique<TaskManager>(id, username, password));
            }
        }
        else if (tag == "BARN") {
            if (currentPlayer) {
                for (std::size_t i = 1; i + 1 < w.size(); i += 2) {
                    int qty = Utils::asInt(w, i + 1, line);
                    currentPlayer->addItem(w[i], qty);
                }
            }
        }
        else if (tag == "FARMCAP") {
            size_t plantCap  = static_cast<size_t>(Utils::asInt(w, 1, line));
            size_t animalCap = static_cast<size_t>(Utils::asInt(w, 2, line));
            if (currentPlayer) {
                while (currentPlayer->getFarm().getPlantCapacity() < plantCap)
                    currentPlayer->getFarm().expandPlantCapacity();
                while (currentPlayer->getFarm().getAnimalCapacity() < animalCap)
                    currentPlayer->getFarm().expandAnimalCapacity();
            }
        }
        else if (tag == "PLANT") {
            std::string type  = w[1];
            int currentCycle  = Utils::asInt(w, 2, line);
            int requiredCycle = Utils::asInt(w, 3, line);
            std::string output = w[4];
            if (currentPlayer) {
                Plant pl(0, type, requiredCycle, output);
                pl.setCurrentCycle(currentCycle);
                currentPlayer->getFarm().addPlant(pl);
            }
        }
        else if (tag == "ANIMAL") {
            std::string type  = w[1];
            int currentCycle  = Utils::asInt(w, 2, line);
            int requiredCycle = Utils::asInt(w, 3, line);
            std::string output = w[4];
            if (currentPlayer) {
                Animal an(0, type, requiredCycle, output);
                an.setCurrentCycle(currentCycle);
                currentPlayer->getFarm().addAnimal(an);
            }
        }
        else if (tag == "MARKET") {
            int id           = Utils::asInt(w, 1, line);
            std::string name = w[2];
            int price        = Utils::asInt(w, 3, line);
            int quantity     = Utils::asInt(w, 4, line);
            market.setProduct(id, name, price, quantity);
        }
        else if (tag == "TASK") {
            int id              = Utils::asInt(w, 1, line);
            std::string product = w[2];
            int quantity        = Utils::asInt(w, 3, line);
            int rewardBalance   = Utils::asInt(w, 4, line);
            int rewardScore     = Utils::asInt(w, 5, line);
            taskBoard.addTaskWithId(id, product, quantity, rewardBalance, rewardScore);
        }
        else {
            throw std::runtime_error("Corrupted save file: unknown tag \"" + tag + "\"");
        }
    }
}