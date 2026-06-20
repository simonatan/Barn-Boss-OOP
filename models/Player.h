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
    bool isPlayer() const override { return true; }

    int  getBalance() const override;
    int  getScore()   const override;
    int  getCycle()   const override;

    void addBalance(int amount)   override;
    void removeBalance(int amount) override;
    void addScore(int amount)     override;
    void advanceCycle()           override;
    void setCycle(int c)          override;

    void addItem(const std::string& item, int qty)        override;
    bool removeItem(const std::string& item, int qty)     override;
    int  getItemQty(const std::string& item) const        override;
    void printBarn() const                                override;
    Barn& getBarn()                                       override;

    Farm& getFarm()         override;
    void checkFarm() const  override;
    void expandCropland()   override;
    void expandFarmland()   override;
};
