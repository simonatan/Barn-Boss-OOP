#include "../engine/CommandExecutor.h"
#include "../engine/GameEngine.h"
#include "../models/Scoreboard.h"
#include "../utils/Exceptions.h"
#include "../utils/Utils.h"
#include "../utils/Validator.h"
#include <iostream>

CommandExecutor::CommandExecutor(GameEngine& engine_) : engine(engine_) {}

void CommandExecutor::requireLoggedIn() const {
    if (!engine.getUserService().getCurrentUser())
        throw AuthenticationException("Not logged in!");
}

Player* CommandExecutor::requirePlayer() const {
    Player* p = engine.getCurrentPlayer();
    if (!p) throw AuthenticationException("Not logged in as Player!");
    return p;
}

MarketManager* CommandExecutor::requireMarketManager() const {
    MarketManager* m = engine.getUserService().getCurrentMarketManager();
    if (!m) throw AuthenticationException("Not logged in as MarketManager!");
    return m;
}

TaskManager* CommandExecutor::requireTaskManager() const {
    TaskManager* t = engine.getUserService().getCurrentTaskManager();
    if (!t) throw AuthenticationException("Not logged in as TaskManager!");
    return t;
}

void CommandExecutor::execute(const Command& cmd) {

    // ---------- AUTH ----------
    if      (cmd.name == "register")       { engine.getUserService().registerUser(cmd.args); }
    else if (cmd.name == "login")          { engine.getUserService().login(cmd.args); }
    else if (cmd.name == "logout")         { engine.getUserService().logout(); }
    else if (cmd.name == "changePassword") { engine.getUserService().changePassword(cmd.args); }
    else if (cmd.name == "reset")          { engine.resetGame(); }

    // ---------- INFO ----------
    else if (cmd.name == "profileInfo") {
        auto* u = engine.getUserService().getCurrentUser();
        if (!u) throw AuthenticationException("Not logged in!");
        u->profileInfo();
    }
    else if (cmd.name == "checkBalance")    { std::cout << "Current Balance: " << requirePlayer()->getBalance() << "\n"; }
    else if (cmd.name == "checkScore")      { std::cout << "Current Score: "   << requirePlayer()->getScore()   << "\n"; }
    else if (cmd.name == "checkBarn")       { requirePlayer()->printBarn(); }
    else if (cmd.name == "checkFarm")       { requirePlayer()->checkFarm(); }
    else if (cmd.name == "openMarketCatalog") { requireLoggedIn(); engine.getMarketService().openCatalog(); }
    else if (cmd.name == "showTaskBoard" || cmd.name == "showTasks") {
        requireLoggedIn(); engine.getTaskService().showTasks();
    }
    else if (cmd.name == "showScoreboard") {
        requireLoggedIn(); Scoreboard::showScoreboard(engine.getUserService().getPlayers());
    }

    // ---------- MARKET MANAGER ----------
    else if (cmd.name == "restock")     { engine.getMarketService().restock(requireMarketManager(), cmd.args); }
    else if (cmd.name == "changePrice") { engine.getMarketService().changePrice(requireMarketManager(), cmd.args); }

    // ---------- TASK MANAGER ----------
    else if (cmd.name == "addTask")    { engine.getTaskService().addTask(requireTaskManager(), cmd.args); }
    else if (cmd.name == "removeTask") { engine.getTaskService().removeTask(requireTaskManager(), cmd.args); }

    // ---------- PLAYER ACTIONS ----------
    else if (cmd.name == "buyItem") {
        if (engine.getMarketService().buy(requirePlayer(), cmd.args))
            requirePlayer()->advanceCycle();
    }
    else if (cmd.name == "sellItem") {
        if (engine.getMarketService().sell(requirePlayer(), cmd.args))
            requirePlayer()->advanceCycle();
    }
    else if (cmd.name == "sowPlant") {
        if (!Validator::isValidCommandSize(cmd.args.size(), 1)) return;
        if (requirePlayer()->sowPlant(Utils::toInt(cmd.args[0])))
            requirePlayer()->advanceCycle();
    }
    else if (cmd.name == "addAnimal") {
        if (!Validator::isValidCommandSize(cmd.args.size(), 1)) return;
        if (requirePlayer()->addAnimal(Utils::toInt(cmd.args[0])))
            requirePlayer()->advanceCycle();
    }
    else if (cmd.name == "harvest") {
        requirePlayer()->harvest();
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
