#include "../utils/Utils.h"
#include "../utils/Exceptions.h"
#include <stdexcept>

int Utils::toInt(const std::string& str) {
    try {
        return std::stoi(str);
    } catch (const std::exception&) {
        throw InvalidCommandException("Invalid number: " + str);
    }
}

std::vector<std::string> Utils::splitWords(const std::string& line) {
    std::vector<std::string> words;
    std::string word;
    for (std::size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == ' ') {
            if (!word.empty()) { words.push_back(word); word.clear(); }
        } else {
            word += c;
        }
    }
    if (!word.empty()) words.push_back(word);
    return words;
}

int Utils::asInt(const std::vector<std::string>& words, std::size_t index, const std::string& line) {
    if (index >= words.size())
        throw std::runtime_error("Corrupted save file: missing field in line \"" + line + "\"");
    try {
        return std::stoi(words[index]);
    } catch (const std::exception& e) {
        throw std::runtime_error("Corrupted save file: expected a number in line \"" + line + "\"");
    }
}