#include "../models/Animal.h"

Animal::Animal(int id_, const std::string& type_, int requiredCycle_, const std::string& output_)
    : id(id_), type(type_), currentCycle(0), requiredCycle(requiredCycle_), output(output_) {}

void Animal::grow() {
    currentCycle++;
}
bool Animal::isReady() const {
    return currentCycle >= requiredCycle;
}
int  Animal::getId() const {
    return id;
}
std::string Animal::getType() const {
    return type;
}
// ?
std::string Animal::getOutput() const {
    return output;
}
int  Animal::getCurrentCycle()  const {
    return currentCycle;
}
int  Animal::getRequiredCycle() const {
    return requiredCycle;
}
void Animal::setCurrentCycle(int c) {
    currentCycle = c;
}
