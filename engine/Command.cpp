#include "../engine/Command.h"
#include "../utils/Utils.h"

Command Command::parse(const std::string& input) {
    Command cmd;
    std::vector<std::string> words = Utils::splitWords(input);
    if (!words.empty()) {
        cmd.name = words[0];
        cmd.args = std::vector(words.begin() + 1, words.end());
    }
    return cmd;
}
