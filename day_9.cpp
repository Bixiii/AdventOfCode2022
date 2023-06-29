#include <iostream>
#include <string>
#include <tuple>
#include "utils.h"
#include <cstdlib>
#include <algorithm>

struct MoveCommand {
  char direction;
  int distance;
  MoveCommand(char direction, int distance) : direction(direction), distance(distance) {};
} typedef MoveCommand;

struct Position {
  int x;
  int y;
  Position(int x, int y): x(x), y(y) {}
  bool operator==(const Position &rhs) const {
      return x==rhs.x &&
          y==rhs.y;
  }
  bool operator!=(const Position &rhs) const {
      return !(rhs==*this);
  };
} typedef Position;

// Task I
void draw_board(Position head_pos, Position tail_pos, const std::vector<std::vector<char>>& map ) {
    for (int i=static_cast<int>(map.size())-1; i>=0; i--) {
        for (auto j=0; j<map[0].size(); j++) {
            Position pos(j,i);
            if (pos == head_pos) {
                std::cout << " H ";
                continue;
            } else if (pos == tail_pos) {
                std::cout << " T ";
                continue;
            }
            std::cout << " " << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Task II
void draw_board(Position head_pos, const std::vector<Position>& rope, const std::vector<std::vector<char>>& map ) {
    for (int i=static_cast<int>(map.size())-1; i>=0; i--) {
        for (auto j=0; j<map[0].size(); j++) {
            Position pos(j,i);
            if (pos == head_pos) {
                std::cout << " H ";
                continue;
            } else if (auto iter = std::find(rope.begin(), rope.end(), pos); iter != rope.end()) {
                std::cout << " " << static_cast<int>(std::distance(rope.begin(), iter))+1 << " ";
                continue;
            }
            std::cout << " " << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Task I
Position move_tail(Position head, Position tail) {
    int x_distance = head.x - tail.x;
    int y_distance = head.y - tail.y;
    // tail does not move
    if (x_distance <= 1 && x_distance >= -1 && y_distance <= 1 && y_distance >= -1) {
        return tail;
    }
    // straight horizontal movement
    if (x_distance == 0 || y_distance == 0){
        return {tail.x + x_distance/2, tail.y + y_distance/2};
    }
    return {tail.x + x_distance/std::abs(x_distance), tail.y + y_distance/std::abs(y_distance)};
}

// Task II
Position move_rope(Position head, std::vector<Position>& rope) {

    for (auto& tail : rope) {

        int x_distance = head.x - tail.x;
        int y_distance = head.y - tail.y;

        if (x_distance <= 1 && x_distance >= -1 && y_distance <= 1 && y_distance >= -1) {
            // tail does not move
        } else if (x_distance == 0 || y_distance == 0){
            tail.x = tail.x + x_distance/2;
            tail.y = tail.y + y_distance/2;
        } else {
            tail.x = tail.x + x_distance/std::abs(x_distance);
            tail.y = tail.y + y_distance/std::abs(y_distance);
        }
        head = tail;
    }
    return rope.back();
}

int main() {

    int challenge_id = 9;
    auto input_data = InputData(challenge_id);

    std::vector<MoveCommand> move_commands;

    for(auto & line : input_data) {
        strip_string(line);
        move_commands.emplace_back(line[0], std::stoi(line.substr(1)));
    }

    int x_pos=0, x_min=0, x_max=0;
    int y_pos=0, y_min=0, y_max=0;
    for (auto move_command : move_commands) {
        if (move_command.direction == 'L') {
            x_pos -= move_command.distance;
            if (x_pos < x_min) {
                x_min = x_pos;
            }
        } else
        if (move_command.direction == 'R') {
            x_pos += move_command.distance;
            if (x_pos > x_max) {
                x_max = x_pos;
            }
        } else
        if (move_command.direction == 'U') {
            y_pos += move_command.distance;
            if (y_pos > y_max) {
                y_max = y_pos;
            }
        } else
        if (move_command.direction == 'D') {
            y_pos -= move_command.distance;
            if (y_pos < y_min) {
                y_min = y_pos;
            }
        }
    }

    std::vector<std::vector<char>> map_one(y_max-y_min+1, std::vector<char>(x_max-x_min+1, '.'));
    std::vector<std::vector<char>> map_two(y_max-y_min+1, std::vector<char>(x_max-x_min+1, '.'));
    Position head(-x_min, -y_min);
    Position tail_one(-x_min, -y_min);
    Position tail_two(-x_min, -y_min);

    std::vector<Position> rope(9, {-x_min, -y_min});

    for (auto move : move_commands) {
        if (move.direction == 'R') {
            for (int dist=0; dist < move.distance; dist++) {
                head.x++;
                tail_one = move_tail(head, tail_one);
                map_one[tail_one.y][tail_one.x] = '#';
                tail_two = move_rope(head, rope);
                map_two[tail_two.y][tail_two.x] = '#';
//                draw_board(head, rope, map);
            }
        } else if (move.direction == 'L') {
            for (int dist=0; dist < move.distance; dist++) {
                head.x--;
                tail_one = move_tail(head, tail_one);
                map_one[tail_one.y][tail_one.x] = '#';
                tail_two = move_rope(head, rope);
                map_two[tail_two.y][tail_two.x] = '#';
//                draw_board(head, rope, map);
            }
        } else if (move.direction == 'U') {
            for (int dist=0; dist < move.distance; dist++) {
                head.y++;
                tail_one = move_tail(head, tail_one);
                map_one[tail_one.y][tail_one.x] = '#';
                tail_two = move_rope(head, rope);
                map_two[tail_two.y][tail_two.x] = '#';
//                draw_board(head, rope, map);
            }
        } else  if (move.direction == 'D') {
            for (int dist = 0; dist < move.distance; dist++) {
                head.y--;
                tail_one = move_tail(head, tail_one);
                map_one[tail_one.y][tail_one.x] = '#';
                tail_two = move_rope(head, rope);
                map_two[tail_two.y][tail_two.x] = '#';
//                draw_board(head, rope, map);
            }
        }
    }
//    draw_board(Position(0,0), Position(0,0), map);

    int score_one = 0;
    for (auto& line : map_one) {
        for (auto field : line) {
            if (field == '#') {
                score_one++;
            }
        }
    }

    int score_two = 0;
    for (auto& line : map_two) {
        for (auto field : line) {
            if (field == '#') {
                score_two++;
            }
        }
    }


    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << score_one << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << score_two << std::endl;

    return 0;
}
