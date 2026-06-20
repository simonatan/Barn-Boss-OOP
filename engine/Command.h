#pragma once

#include <string>
#include <vector>

struct Command {
    std::string name;
    std::vector<std::string> args;

    static Command parse(const std::string& input);
};