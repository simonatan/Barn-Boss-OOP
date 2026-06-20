#include "../models/Task.h"
#include <iostream>

Task::Task(int id_, const std::string& product_, int quantity_, int rewardBalance_, int rewardScore_)
    : id(id_), requiredProduct(product_), requiredQuantity(quantity_),
      rewardBalance(rewardBalance_), rewardScore(rewardScore_) {}

int Task::getId() const { return id; }
std::string Task::getProduct() const { return requiredProduct; }
int Task::getQuantity() const { return requiredQuantity; }
int Task::getRewardBalance() const { return rewardBalance; }
int Task::getRewardScore() const { return rewardScore; }

void Task::print() const {
    std::cout << id << ". Deliver " << requiredQuantity << " " << requiredProduct
              << " → Reward: " << rewardBalance << " Balance, " << rewardScore << " Score\n";
}
