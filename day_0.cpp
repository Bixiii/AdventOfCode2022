#include <iostream>
#include <string>
#include "utils.h"

int main() {

    int challenge_id = 0;
    auto input_data = InputData(challenge_id);

    for(auto & line : input_data) {
        strip_string(line);
        std::cout << line << std::endl;
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << std::endl;

    return 0;
}
