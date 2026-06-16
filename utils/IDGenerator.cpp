#include "../utils/IDGenerator.h"

int IDGenerator::currentId = 1;

int IDGenerator::generateId() { return currentId++; }

void IDGenerator::reset() { currentId = 1; }