#include <iostream>
#include <string>
#include <set>
#include "utils.h"

int main()
{

    int challenge_id = 6;
    auto input_data = InputData(challenge_id);

    int kWindowSizePacket = 4;
    int packet_start_idx = -1;
    for(auto & line : input_data) {
        strip_string(line);
        for (int i=0; i<line.size()-kWindowSizePacket; i++) {
            std::set<char> window;
            for (int j=0; j<kWindowSizePacket; j++) {
                window.insert(line[i+j]);
            }
            if (window.size() == kWindowSizePacket) {
//                std::cout << "Sequence starts at idx: " << i+kWindowSizePacket << std::endl;
                packet_start_idx = i+kWindowSizePacket;
                break;
            }
        }
    }

    int kWindowSizeMessage = 14;
    int message_start_idx = -1;
    for(auto & line : input_data) {
        strip_string(line);
        for (int i=0; i<line.size()-kWindowSizeMessage; i++) {
            std::set<char> window;
            for (int j=0; j<kWindowSizeMessage; j++) {
                window.insert(line[i+j]);
            }
            if (window.size() == kWindowSizeMessage) {
//                std::cout << "Sequence starts at idx: " << i+kWindowSizeMessage << std::endl;
                message_start_idx = i+kWindowSizeMessage;
                break;
            }
        }
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << packet_start_idx << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << message_start_idx << std::endl;

    return 0;
}
