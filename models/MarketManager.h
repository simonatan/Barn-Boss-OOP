#pragma once

#include "../models/User.h"

class MarketManager : public User {
public:
    MarketManager(int id, const std::string& username, const std::string& password);
    [[nodiscard]] std::string getType() const override;
};

