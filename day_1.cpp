#include <iostream>
#include <string>
#include "utils.h"
#include <numeric>
#include <algorithm>

class Elf {
 private:
    std::vector<int> food_items_;
 public:
    void AddFoodItem(int calories) {
        food_items_.push_back(calories);
    }
    int TotalCalories() {
        return std::accumulate(food_items_.begin(), food_items_.end(), 0);
    }
};

int main() {

    int challenge_id = 1;
    auto input_data = InputData(challenge_id);

    std::vector<Elf> elfs;

    std::vector<int> elf;
    elfs.emplace_back();
    for(auto & line : input_data) {
        std::string striped_line = line.substr(0, line.length()-1);
        if (striped_line.empty()) {
            elfs.emplace_back();
            continue;
        }
        if (!striped_line.empty()){
            elfs.back().AddFoodItem(std::stoi(striped_line));
        }
    }

    std::vector<int> total_calories_per_elf;
    for (auto& current_elf : elfs) {
        total_calories_per_elf.push_back(current_elf.TotalCalories());
    }
    std::sort(total_calories_per_elf.begin(), total_calories_per_elf.end());
    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << total_calories_per_elf.back() << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << std::accumulate(total_calories_per_elf.begin()+(total_calories_per_elf.size()-3), total_calories_per_elf.end(), 0) << std::endl;

    return 0;
}
