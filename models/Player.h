#pragma once

#include "../models/User.h"
#include "../models/Farm.h"
#include "../models/Barn.h"
#include <string>

class Player : public User {
    Barn barn;
    Farm farm;
    int balance;
    int score;
    int cycle;

public:
    Player(int id, const std::string& username, const std::string& password);

    std::string getType() const override;
    void profileInfo() const override;

    int getBalance() const;
    int getScore() const;
    int getCycle() const;

    void addBalance(int amount);
    void removeBalance(int amount);
    void addScore(int amount);
    void advanceCycle();
    void setCycle(int c);

    void addItem(const std::string& item, int qty);
    bool removeItem(const std::string& item, int qty);
    int getItemQty(const std::string& item) const;
    void printBarn() const;
    Barn& getBarn();

    Farm& getFarm();
    void checkFarm() const;
    void expandCropland();
    void expandFarmland();
};
