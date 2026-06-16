#include "../models/Scoreboard.h"
#include <iostream>
#include <algorithm>

static bool comparePlayers(const Player* a, const Player* b) {
    if (a->getScore() != b->getScore())
        return a->getScore() > b->getScore();
    if (a->getBalance() != b->getBalance())
        return a->getBalance() > b->getBalance();
    return a->getId() < b->getId();
}

void Scoreboard::showScoreboard(const std::vector<Player*>& players) {
    std::vector<Player*> sorted = players;
    std::sort(sorted.begin(), sorted.end(), comparePlayers);

    std::cout << "=== SCOREBOARD ===\n";
    int rank = 1;
    for (auto p : sorted) {
        std::cout << rank << ". " << p->getUsername()
                  << " | Score: " << p->getScore()
                  << " | Balance: " << p->getBalance() << "\n";
        rank++;
    }
}

