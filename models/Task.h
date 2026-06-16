#pragma once

#include <string>

class Task {
    int id;
    std::string requiredProduct;
    int requiredQuantity;
    int rewardBalance;
    int rewardScore;

public:
    Task(int id, const std::string& product, int quantity, int rewardBalance, int rewardScore);

    int getId() const;
    std::string getProduct() const;
    int getQuantity() const;
    int getRewardBalance() const;
    int getRewardScore() const;

    void print() const;
};
