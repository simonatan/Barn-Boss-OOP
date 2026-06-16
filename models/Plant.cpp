#include "../models/Plant.h"

Plant::Plant(int id_, const std::string& type_, int requiredCycle_, const std::string& output_)
    : id(id_), type(type_), currentCycle(0), requiredCycle(requiredCycle_), output(output_) {}

void Plant::grow() {
    currentCycle++;
}
bool Plant::isReady() const {
    return currentCycle >= requiredCycle;
}
int  Plant::getId() const { return id; }
std::string Plant::getType() const { return type; }
std::string Plant::getOutput() const { return output; }
int  Plant::getCurrentCycle() const { return currentCycle; }
int  Plant::getRequiredCycle() const { return requiredCycle; }
void Plant::setCurrentCycle(int c) { currentCycle = c; }
