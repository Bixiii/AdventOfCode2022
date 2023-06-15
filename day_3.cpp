#include <iostream>
#include <string>
#include "utils.h"
#include <numeric>
#include <algorithm>
#include <unordered_set>

int get_item_score(char item) {
    int score = 0;
    if (item <= 'Z') {
        score += item - 'A' + 27;
    } else {
        score += item - 'a' + 1;
    }
    return score;
}

int main() {

    int challenge_id = 3;
    auto input_data = InputData(challenge_id);

    int total_score = 0;
    for(auto & line : input_data) {
        strip_string(line);
        int middle = line.length() / 2;
        auto compartment_one = line.substr(0, middle);
        auto compartment_two = line.substr(middle);

        for (auto item : compartment_one) {
            char duplicate_item = *std::find(compartment_two.begin(), compartment_two.end(), item);
            if (duplicate_item) {
                total_score += get_item_score(duplicate_item);
                break;
            }
        }
    }

    int total_badge_score = 0;
    for(int i=0; i<input_data.size(); i+=3) {
        std::unordered_set<char> items_first_elf(input_data[i].begin(), input_data[i].end());
        std::unordered_set<char> items_second_elf(input_data[i+1].begin(), input_data[i+1].end());
        std::unordered_set<char> items_third_elf(input_data[i+2].begin(), input_data[i+2].end());

        for (char item : items_first_elf) {
            if (items_second_elf.count(item) && items_third_elf.count(item)) {
                total_badge_score += get_item_score(item);
            }
        }
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << total_score << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << total_badge_score << std::endl;

    return 0;
}
