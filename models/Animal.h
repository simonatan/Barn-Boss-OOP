#pragma once

#include <string>

class Animal {
    int id;
    std::string type;
    int currentCycle;
    int requiredCycle;
    std::string output;

public:
    Animal(int id, const std::string& type, int requiredCycle, const std::string& output);

    void grow();
    bool isReady() const;

    int getId() const;
    std::string getType() const;
    std::string getOutput() const;
    int getCurrentCycle() const;
    int getRequiredCycle() const;
    void setCurrentCycle(int c);
};
