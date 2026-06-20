#include "../engine/Command.h"

Command Command::parse(const std::string& input) {
    Command cmd;
    std::string word;

    for (std::size_t i = 0; i < input.size(); i++) {
        char c = input[i];

        if (c == ' ') {
            if (!word.empty()) {
                if (cmd.name.empty()) cmd.name = word;
                else cmd.args.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }

    if (!word.empty()) {
        if (cmd.name.empty()) cmd.name = word;
        else cmd.args.push_back(word);
    }

    return cmd;
}