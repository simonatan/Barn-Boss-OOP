#pragma once

class IDGenerator {
    static int currentId;

public:
    static int generateId();
    static void reset();
};