#include <iostream>
#include <string>
#include <regex>
#include <utility>
#include "utils.h"

class Entry {
 private:
    std::string name_;
    bool is_file_ = false;
    long size_ = 0;

    Entry* parent_ = nullptr;
    std::vector<Entry> children_;

    const long kCutOffSize = 100000; // for task one

 public:
    explicit Entry(std::string  name, bool is_file) : name_(std::move(name)), is_file_(is_file) {}

    void AddFile(const std::string& name, long size){
        Entry file(name, true);
        file.size_ = size;
        file.parent_ = this;
        children_.push_back(std::move(file));
    }
    void AddSubDirectory(const std::string& name){
        Entry dir(name, false);
        dir.parent_ = this;
        children_.push_back(std::move(dir));
    }
    Entry* FindChild(const std::string& name) {
        for (auto& child : children_) {
            if (child.name_ == name) {
                return &child;
            }
        }
        return nullptr;
    }

    Entry* Parent() {
        return parent_;
    }

    std::string Name() {
        return name_;
    }

    long CalculateSize() {
        if (is_file_) {
            return size_;
        }
        for (auto& child : children_) {
            size_ += child.CalculateSize();
        }
        return size_;
    }

    long TaskOne() {
        static long task_one_score = 0;
        if (!is_file_) {
            if (size_ < kCutOffSize) {
                task_one_score += size_;
            }
        }
        for (auto& child : children_) {
            child.TaskOne();
        }
        return task_one_score;
    }

    long TaskTwo(long space_to_free) {
        static long task_two_score = std::numeric_limits<long>::max();
        if (!is_file_) {
            if (size_ > space_to_free) {
                if (size_ < task_two_score) {
                    task_two_score = size_;
                }
            }
        }
        for (auto& child : children_) {
            child.TaskTwo(space_to_free);
        }
        return task_two_score;
    }
};

int main() {

    int challenge_id = 7;
    auto input_data = InputData(challenge_id);

    std::regex command_pattern_cd(R"(\$ cd (.*))");
    std::regex command_pattern_ls(R"(\$ ls)");
    std::regex output_pattern_dir(R"(dir (.*))");
    std::regex output_pattern_file(R"((^\d+) (.*))");

    Entry root("/", false);
    Entry* current_dir = &root;

    // build the tree
    int i = 0;
    while (i<input_data.size()) {

        std::string line = input_data[i];
        strip_string(line);

        std::smatch matches;

        if(std::regex_search(line, matches, command_pattern_cd)) {
            std::string dir_name = matches.str(1);
//            std::cout << "$ cd " << dir_name << std::endl;
            if(dir_name != "/") {
                if(dir_name == "..") {
                    current_dir = current_dir->Parent();
                } else {
                    current_dir = current_dir->FindChild(dir_name);
                }
            }

        } else if (std::regex_search(line, matches, command_pattern_ls)) {
//            std::cout << "$ ls" << std::endl;
            line = input_data[++i];
            strip_string(line);
            while (std::regex_search(line, output_pattern_dir) || std::regex_search(line, output_pattern_file)) {
                if (std::regex_search(line, matches, output_pattern_dir)) {
                    std::string dir_name = matches.str(1);
//                    std::cout << "dir " << dir_name << std::endl;
                    current_dir->AddSubDirectory(dir_name);
                } else if (std::regex_search(line, matches, output_pattern_file)) {
                    std::string file_name = matches.str(2);
                    long file_size = std::stol(matches.str(1));
//                    std::cout << file_size << " " << file_name << std::endl;
                    current_dir->AddFile(file_name, file_size);
                }
                line = input_data[++i];
                strip_string(line);
            }
            line = input_data[--i];
            strip_string(line);
            continue;
        }
        i++;
    }

    long total_size = root.CalculateSize();

    const long kDiskSpace = 70000000;
    const long kUpdateSize = 30000000;
    long available_space = kDiskSpace - total_size;
    long space_to_free = kUpdateSize - available_space;

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << root.TaskOne() << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << root.TaskTwo(space_to_free) << std::endl;

    return 0;
}
