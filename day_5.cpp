#include <iostream>
#include <string>
#include <stack>
#include <regex>
#include "utils.h"

int main() {

    int challenge_id = 5;
    auto input_data = InputData(challenge_id);

    std::vector<std::vector<char>> cargo;
    std::vector<std::string> move_commands;
    int box_size = 3; // 3 chars for one box [*]
    int distance = 1; // one char between two boxes horizontally

    int separator_line_idx = -1;
    int num_stacks = 0;
    for(int line_num=0; line_num < input_data.size(); line_num++) {

        auto& line = input_data[line_num];
        strip_string(line);

        if (line.empty()) { //search empty line that separates the two sections
            separator_line_idx = line_num;
            std::regex pattern(R"(\d+)");
            std::sregex_iterator iter(input_data[separator_line_idx-1].begin(), input_data[separator_line_idx-1].end(), pattern);
            std::sregex_iterator end;

            std::smatch last_match;
            while(iter != end) {
                last_match = *iter;
                ++iter;
            }
            int num_stacks = std::stoi(last_match[0]);
            cargo.resize(num_stacks);
            continue;
        }
    }

    for(int line_num = 0; line_num < separator_line_idx - 1; line_num++) {
        for(int char_num = 0; char_num < input_data[line_num].size(); char_num++) {
            if (input_data[line_num][char_num] == '[') {
                int stack_id = char_num / (box_size + distance);
                cargo[stack_id].insert(cargo[stack_id].begin(), input_data[line_num][char_num + 1]);
            }
        }
    }

    for(int line_num=separator_line_idx + 1; line_num < input_data.size(); line_num++) {
        move_commands.push_back(input_data[line_num]);
    }

    std::vector<std::vector<char>> copy_cargo(cargo); // backup for part two

    std::regex pattern(R"(move (\d+) from (\d+) to (\d+))");
    std::smatch matches;
    for (const auto& move_command : move_commands) {
        int start_stack, end_stack, num_elements;
        if (std::regex_search(move_command, matches, pattern)) {
            num_elements = std::stoi(matches[1]);
            start_stack = std::stoi(matches[2]) - 1;
            end_stack = std::stoi(matches[3]) - 1;
            for (int i=0; i<num_elements; i++) {
                char element_to_move = cargo[start_stack].back();
                cargo[start_stack].pop_back();
                cargo[end_stack].push_back(element_to_move);
            }
        }
    }

    std::string solution_line_part_one;
    for (auto stack : cargo) {
        solution_line_part_one += stack.back();
    }

    cargo = copy_cargo;
    for (const auto& move_command : move_commands) {
        int start_stack, end_stack, num_elements;
        if (std::regex_search(move_command, matches, pattern)) {
            num_elements = std::stoi(matches[1]);
            start_stack = std::stoi(matches[2]) - 1;
            end_stack = std::stoi(matches[3]) - 1;

            std::vector<char> elements_to_move(cargo[start_stack].end() - num_elements, cargo[start_stack].end());
            cargo[start_stack].erase(cargo[start_stack].end() - num_elements, cargo[start_stack].end());
            cargo[end_stack].insert(cargo[end_stack].end(), elements_to_move.begin(), elements_to_move.end());
        }
    }

    std::string solution_line_part_two;
    for (auto stack : cargo) {
        solution_line_part_two += stack.back();
    }



    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << solution_line_part_one << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << solution_line_part_two << std::endl;

    return 0;
}
