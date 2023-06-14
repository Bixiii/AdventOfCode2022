#include <iostream>
#include <string>
#include "utils.h"
#include <numeric>
#include <algorithm>

class HandSign {
 public:
    enum HandSignName {
      Rock,
      Paper,
      Scissors
    } typedef HandSignName;

    HandSign(HandSign opponent_choice, char outcome) {
        Outcome desired_outcome = decode_outcome(outcome);

        if (opponent_choice.chosen_hand_sign_ == Rock) {
            if (desired_outcome == Win) {
                chosen_hand_sign_ = Paper;
            }
            else if (desired_outcome == Lose) {
                chosen_hand_sign_ = Scissors;
            }
            else {
                chosen_hand_sign_ = Rock;
            }
        }

        else if (opponent_choice.chosen_hand_sign_ == Paper) {
            if (desired_outcome == Win) {
                chosen_hand_sign_ = Scissors;
            }
            else if (desired_outcome == Lose) {
                chosen_hand_sign_ = Rock;
            }
            else {
                chosen_hand_sign_ = Paper;
            }
        }

        else if (opponent_choice.chosen_hand_sign_ == Scissors) {
            if (desired_outcome == Win) {
                chosen_hand_sign_ = Rock;
            }
            else if (desired_outcome == Lose) {
                chosen_hand_sign_ = Paper;
            }
            else {
                chosen_hand_sign_ = Scissors;
            }
        }
    }

    HandSign(char coded_sign) {
        switch (coded_sign) {
            case 'A':
                chosen_hand_sign_ = Rock;
                break;
            case 'B':
                chosen_hand_sign_ = Paper;
                break;
            case 'C':
                chosen_hand_sign_ = Scissors;
                break;
            case 'X':
                chosen_hand_sign_ = Rock;
                break;
            case 'Y':
                chosen_hand_sign_ = Paper;
                break;
            case 'Z':
                chosen_hand_sign_ = Scissors;
                break;
            default:
                break;
        }
    }

    int PlayGame(HandSign other) {
        int game_score = 0;
        if (chosen_hand_sign_ == Rock) {
            game_score += 1;
            if (other.chosen_hand_sign_ == Scissors) {
                game_score +=6;
            }
            else if (other.chosen_hand_sign_ == Paper) {
                game_score +=0;
            }
            else {
                game_score +=3;
            }
        }
        if (chosen_hand_sign_ == Paper) {
            game_score += 2;
            if (other.chosen_hand_sign_ == Rock) {
                game_score +=6;
            }
            else if (other.chosen_hand_sign_ == Scissors) {
                game_score +=0;
            }
            else {
                game_score +=3;
            }
        }
        if (chosen_hand_sign_ == Scissors) {
            game_score += 3;
            if (other.chosen_hand_sign_ == Paper) {
                game_score +=6;
            }
            else if (other.chosen_hand_sign_ == Rock) {
                game_score +=0;
            }
            else {
                game_score +=3;
            }
        }
        return game_score;
    }


 private:

    HandSignName chosen_hand_sign_;

    enum Outcome {
      Win,
      Lose,
      Draw,
      Error

    } typedef Outcome;

    static Outcome decode_outcome(char outcome) {

        switch (outcome) {
            case 'X':
                return Lose;
            case 'Y':
                return Draw;
            case 'Z':
                return Win;
        }
        std::cerr << "Invalid input as desired output <" << outcome << ">, must be <'X', 'Y', 'Z'>" << std::endl;
        return Error;
    }
};

int main() {

    int challenge_id = 2;
    auto input_data = InputData(challenge_id);


    int total_game_score = 0;
    for (auto& line : input_data) {
        std::string striped_line = line.substr(0, line.length()-1);
        auto elf_choice = HandSign(striped_line[0]);
        auto my_choice = HandSign(striped_line[2]);
        total_game_score += my_choice.PlayGame(elf_choice);
    }

    int total_game_score_new_decryption = 0;
    for (auto& line : input_data) {
        std::string striped_line = line.substr(0, line.length()-1);
        auto elf_choice = HandSign(striped_line[0]);
        auto my_choice = HandSign(elf_choice, striped_line[2]);
        total_game_score_new_decryption += my_choice.PlayGame(elf_choice);
    }


    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << total_game_score << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << total_game_score_new_decryption << std::endl;

    return 0;
}
