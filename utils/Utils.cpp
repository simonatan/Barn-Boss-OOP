#include "../utils/Utils.h"
#include <sstream>
#include <stdexcept>

int Utils::toInt(const std::string& str) {
    return std::stoi(str);
}