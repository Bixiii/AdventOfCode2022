#include <iostream>
#include <string>
#include <regex>
#include "utils.h"

bool is_contained(int first_start, int first_end, int second_start, int second_end) {

    if (first_start > first_end) {
        int tmp = first_start;
        first_start = first_end;
        first_end = tmp;
    }
    if (second_start > second_end) {
        int tmp = second_start;
        second_start = second_end;
        second_end = tmp;
    }

    // first is fully contained in second
    if (first_start >= second_start && first_end <= second_end) {
        return true;
    }
    // second is fully contained in first
    if (second_start >= first_start && second_end <= first_end) {
        return true;
    }
    return false;
}

bool is_overlapping(int first_start, int first_end, int second_start, int second_end) {

    if (is_contained(first_start, first_end, second_start, second_end)) {
        return true;
    }

    if (first_start > first_end) {
        int tmp = first_start;
        first_start = first_end;
        first_end = tmp;
    }
    if (second_start > second_end) {
        int tmp = second_start;
        second_start = second_end;
        second_end = tmp;
    }

    if (first_start <= second_start && first_end >= second_start && first_end <= second_end) {
        return true;
    }

    if (second_start <= first_start && second_end >= first_start && second_end <= first_end) {
        return true;
    }

    return false;
}

int main() {

    int challenge_id = 4;
    auto input_data = InputData(challenge_id);

    std::regex pattern(R"((\d+)-(\d+),(\d+)-(\d+))");
    std::smatch matches;

    int pairs_fully_contained = 0;
    int pairs_overlap = 0;
    for(auto & line : input_data) {
        strip_string(line);
        if (std::regex_search(line, matches, pattern)) {
            int first_elf_start = std::stoi(matches[1]);
            int first_elf_end = std::stoi(matches[2]);
            int second_elf_start = std::stoi(matches[3]);
            int second_elf_end = std::stoi(matches[4]);
//            std::cout << first_elf_start << "-" << first_elf_end << "," << second_elf_start << "-" << second_elf_end;
//            std::cout << " -> " << is_contained(first_elf_start, first_elf_end, second_elf_start, second_elf_end) << std::endl;
            if (is_contained(first_elf_start, first_elf_end, second_elf_start, second_elf_end)) {
                pairs_fully_contained++;
            }
            if (is_overlapping(first_elf_start, first_elf_end, second_elf_start, second_elf_end)) {
                pairs_overlap ++;
            }
        }
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << pairs_fully_contained << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << pairs_overlap << std::endl;

    return 0;
}
