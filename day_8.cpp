#include <iostream>
#include <string>
#include "utils.h"

class Tree {
 private:
    int height_ = -1;
    bool visible_from_top_ = false;
    bool visible_from_bottom_ = false;
    bool visible_from_left_ = false;
    bool visible_from_right_ = false;
 public:
    void SetHeight(int height){
        height_ = height;
    }
    void SetVisibleFromTop() {
        visible_from_top_ = true;
    };
    void SetVisibleFromBottom() {
        visible_from_bottom_ = true;
    };
    void SetVisibleFromLeft() {
        visible_from_left_ = true;
    };
    void SetVisibleFromRight() {
        visible_from_right_ = true;
    };
    int Height() {
        return height_;
    }

    bool Visible() {
        return visible_from_left_ || visible_from_right_ || visible_from_top_ || visible_from_bottom_;
    }
};

int main() {

    int challenge_id = 8;
    auto input_data = InputData(challenge_id);

    auto rows = input_data.size();
    std::string first_row = input_data[0];
    strip_string(first_row);
    auto cols = first_row.size();
    std::vector<std::vector<Tree>> tree_grid(rows+2, std::vector<Tree>(cols+2));

    // init tree grid padded with -1 on boarders
    for(int row=1; row<rows+1; row++) {
        for(int col=1; col<cols+1; col++){
            int tree_height = input_data[row-1][col-1]-'0';
            tree_grid[row][col].SetHeight(tree_height);
        }
    }

    // PART I

    for(auto row=1; row<rows+1; row++) {
        int left_max = -1;
        for(auto col=1; col<cols+1; col++){
            if (tree_grid[row][col].Height() > left_max) {
                tree_grid[row][col].SetVisibleFromLeft();
                left_max = tree_grid[row][col].Height();
            }
        }
    }

    for(auto row=1; row<rows+1; row++) {
        int right_max = -1;
        for(auto col=cols; col>0; col--){
            if (tree_grid[row][col].Height() > right_max) {
                tree_grid[row][col].SetVisibleFromRight();
                right_max = tree_grid[row][col].Height();
            }
        }
    }

    for(auto col=1; col<cols+1; col++) {
        int top_max = -1;
        for(auto row=1; row<rows+1; row++){
            if (tree_grid[row][col].Height() > top_max) {
                tree_grid[row][col].SetVisibleFromTop();
                top_max = tree_grid[row][col].Height();
            }
        }
    }

    for(auto col=1; col<cols+1; col++) {
        int bottom_max = -1;
        for(auto row=rows; row>0; row--){
            if (tree_grid[row][col].Height() > bottom_max) {
                tree_grid[row][col].SetVisibleFromBottom();
                bottom_max = tree_grid[row][col].Height();
            }
        }
    }

    int visible_trees = 0;
    for (const auto& row : tree_grid) {
        for (auto tree : row) {
            if (tree.Visible()) {
//                std::cout << " * ";
                visible_trees++;
            } else {
//                std::cout << " . ";
            }
        }
//        std::cout << std::endl;
    }

    // PART II

    int max_view_score = 0;
    for(auto row=1; row<rows+1; row++) {
        for(auto col=1; col<cols+1; col++){
            int tree_height = tree_grid[row][col].Height();

            // left
            int view_row = row;
            int view_col = col;
            int view_left = 0;
            do {
                view_col--;
                if (tree_grid[view_row][view_col].Height() < 0) {
                    break;
                }
                view_left += 1;
            } while (tree_grid[view_row][view_col].Height() < tree_height);


            // top
            view_row = row;
            view_col = col;
            int view_top = 0;
            do {
                view_row--;
                if (tree_grid[view_row][view_col].Height() < 0) {
                    break;
                }
                view_top += 1;
            } while (tree_grid[view_row][view_col].Height() < tree_height);

            // right
            view_row = row;
            view_col = col;
            int view_right = 0;
            do {
                view_col++;
                if (tree_grid[view_row][view_col].Height() < 0) {
                    break;
                }
                view_right += 1;
            } while (tree_grid[view_row][view_col].Height() < tree_height);

            // bottom
            view_row = row;
            view_col = col;
            int view_bottom = 0;
            do {
                view_row++;
                if (tree_grid[view_row][view_col].Height() < 0) {
                    break;
                }
                view_bottom += 1;
            } while (tree_grid[view_row][view_col].Height() < tree_height);

            int view_score = view_top*view_left*view_right*view_bottom;
            if (view_score > max_view_score) {
                max_view_score = view_score;
            }
        }
    }

    std::cout << "\n*** Results ***" << std::endl;
    std::cout << "Day " << challenge_id << " - Part 1: " << visible_trees << std::endl;
    std::cout << "Day " << challenge_id << " - Part 2: " << max_view_score << std::endl;

    return 0;
}
