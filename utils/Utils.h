#pragma once

#include <string>
#include <vector>

class Utils {
public:
    static int toInt(const std::string& str);

    static std::vector<std::string> splitWords(const std::string& line);

    static int asInt(const std::vector<std::string>& words, std::size_t index, const std::string& line);
};