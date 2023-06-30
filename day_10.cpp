#include <iostream>
#include <string>
#include <regex>
#include "utils.h"

int main() {

    int challenge_id = 10;
    auto input_data = InputData(challenge_id);

    std::vector<std::string> commands;


    for(auto & line : input_data) {
        strip_string(line);
        if (line.starts_with("addx")) {
            commands.emplace_back("dummy"); // insert dummies for longer operations
        }
        commands.emplace_back(line);
//        std::cout << line << std::endl;
    }

    std::regex pattern(R"(addx (.*))");
    std::smatch matches;

    int clock = 0;
    int x_register = 1;
    int sum = 0;
    std::vector<int> important_ticks = {20, 60, 100, 140, 180, 220};

    for (const auto& command : commands) {
        clock++;
        if (std::find(important_ticks.begin(), important_ticks.end(), clock) != important_ticks.end()) {
//            std::cout << ">> tick: " << clock << " >> x: " << x_register << " >> product: " << clock*x_register << std::endl;
            sum += (clock*x_register);
        }
        if (std::regex_search(command, matches, pattern)) {
            x_register += std::stoi(matches[1]);
        }
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << sum  << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << std::endl;

    return 0;
}
