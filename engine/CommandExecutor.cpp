#include "../engine/CommandExecutor.h"
#include "../engine/GameEngine.h"
#include "../models/Scoreboard.h"
#include "../utils/Exceptions.h"
#include "../services/FarmService.h"
#include <iostream>

CommandExecutor::CommandExecutor(GameEngine& engine_) : engine(engine_) {}

User* CommandExecutor::requirePlayer() const {
    User* p = engine.getCurrentPlayer();
    if (!p) throw AuthenticationException("Not logged in as Player!");
    return p;
}

void CommandExecutor::execute(const Command& cmd) {

    // ---------- AUTH ----------
    if (cmd.name == "register") { engine.getUserService().registerUser(cmd.args); }
    else if (cmd.name == "login") { engine.getUserService().login(cmd.args); }
    else if (cmd.name == "logout") { engine.getUserService().logout(); }
    else if (cmd.name == "changePassword") { engine.getUserService().changePassword(cmd.args); }

    // ---------- INFO ----------
    else if (cmd.name == "profileInfo") {
        auto* u = engine.getUserService().getCurrentUser();
        if (!u) throw AuthenticationException("Not logged in!");
        u->profileInfo();
    }
    else if (cmd.name == "checkBalance") { std::cout << "Current Balance: " << requirePlayer()->getBalance() << "\n"; }
    else if (cmd.name == "checkScore") { std::cout << "Current Score: "   << requirePlayer()->getScore()   << "\n"; }
    else if (cmd.name == "checkBarn") { requirePlayer()->printBarn(); }
    else if (cmd.name == "checkFarm") { requirePlayer()->checkFarm(); }
    else if (cmd.name == "openMarketCatalog") { engine.getMarketService().openCatalog(); }
    else if (cmd.name == "showTaskBoard" || cmd.name == "showTasks") {
        engine.getTaskService().showTasks();
    }
    else if (cmd.name == "showScoreboard") {
        std::vector<User*> players;
        for (auto* u : engine.getUserService().getAllUsers())
            if (u->isPlayer()) players.push_back(u);
        Scoreboard::showScoreboard(players);
    }

    // ---------- MARKET MANAGER ----------
    else if (cmd.name == "restock") {
        engine.getMarketService().restock(engine.getUserService().getCurrentUser(), cmd.args);
    }
    else if (cmd.name == "changePrice") {
        engine.getMarketService().changePrice(engine.getUserService().getCurrentUser(), cmd.args);
    }

    // ---------- TASK MANAGER ----------
    else if (cmd.name == "addTask") {
        engine.getTaskService().addTask(engine.getUserService().getCurrentUser(), cmd.args);
    }
    else if (cmd.name == "removeTask") {
        engine.getTaskService().removeTask(engine.getUserService().getCurrentUser(), cmd.args);
    }

    // ---------- PLAYER ACTIONS ----------
    else if (cmd.name == "buyItem") {
        if (engine.getMarketService().buy(engine.getUserService().getCurrentUser(), cmd.args))
            if (auto* p = engine.getCurrentPlayer())
                p->advanceCycle();
    }
    else if (cmd.name == "sellItem") {
        if (engine.getMarketService().sell(engine.getUserService().getCurrentUser(), cmd.args))
            if (auto* p = engine.getCurrentPlayer())
                p->advanceCycle();
    }
    else if (cmd.name == "sowPlant") {
        if (FarmService::sowPlant(requirePlayer(), cmd.args))
            requirePlayer()->advanceCycle();
    }
    else if (cmd.name == "addAnimal") {
        if (FarmService::addAnimal(requirePlayer(), cmd.args)) requirePlayer()->advanceCycle();
    }
    else if (cmd.name == "harvest") {
        FarmService::harvest(requirePlayer());
    }
    else if (cmd.name == "expandCropland") {
        auto* p = requirePlayer();
        p->expandCropland();
        p->advanceCycle();
    }
    else if (cmd.name == "expandFarmland") {
        auto* p = requirePlayer();
        p->expandFarmland();
        p->advanceCycle();
    }
    else if (cmd.name == "completeTask") {
        if (engine.getTaskService().completeTask(requirePlayer(), cmd.args))
            requirePlayer()->advanceCycle();
    }

    else { std::cout << "Command not recognized.\n"; }
}
