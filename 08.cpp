#include "parser.h"

class TreeHouse {
    std::vector<std::vector<char>> forest;

public:
    TreeHouse(std::string filename) {
        auto lines = Parser::readLines(filename);
        for (const auto & l : lines) {
            std::vector<char> row;
            for (char c : l) row.emplace_back(c);
            forest.emplace_back(row);
        }
    }

    bool isVisible(size_t x, size_t y) {
        char height = forest[y][x]; 
        // going in each direction to see if theres a taller tree
        bool west{true};
        for (int i = 0; i < x; ++i) 
            if (height <= forest[y][i]) {
                 west = false;
                 break;
            }

        bool east{true};
        for (int i = x + 1; i < forest[0].size(); ++i)
            if (height <= forest[y][i]) {
                east = false;
                break;
            }

        bool north{true};
        for (int i = 0; i < y; ++i)
            if (height <= forest[i][x]) {
                north = false;
                break;
            }
        
        bool south{true};
        for (int i = y + 1; i < forest.size(); ++i) 
            if (height <= forest[i][x]) {
                south = false;
                break;
            }
       
        return (west || east || north || south);
    }
    
    int numVisible() {
        // trees on edges
        int num = 2 * forest.size() + 2 * forest[0].size() - 4;

        for (size_t y = 1; y < forest.size() - 1; ++y) {
            for (size_t x = 1; x < forest[0].size() - 1; ++x) 
                if (isVisible(x, y)) num++;
        }
        
        return num;
    }

    int getScenicScore(size_t x, size_t y) {
        char height = forest[y][x];

        // going in each direction until tree with equal or greater height reached
        int west{0};
        for (int i = x - 1; i >= 0; --i) {
            west++;
            if (height <= forest[y][i]) break;
        }

        int east{0};
        for (int i = x + 1; i < forest[y].size(); ++i) {
            east++;
            if (height <= forest[y][i]) break;
        }

        int north{0};
        for (int i = y - 1; i >= 0; --i) {
            north++;
            if (height <= forest[i][x]) break;
        }

        int south{0};
        for (int i = y + 1; i < forest.size(); ++i) {
            south++;
            if (height <= forest[i][x]) break;
        }
        
        return west * east * north * south;
    }

    int maxScenicScore() {
        int max{0};
        for (int y = 1; y < forest.size() - 1; ++y) {
            for (int x = 1; x < forest[y].size() - 1; ++x) {
                int score = getScenicScore(x, y);
                if (max <= score) max = score; 
            }
        }

        return max;
    }

};

int main() {
    fmt::print("AOC-22 #08\n");
    
    TreeHouse th = {"../data/08.txt"};

    fmt::print("number of visible trees: {}\n", th.numVisible());
    fmt::print("scenic score of best position: {}\n", th.maxScenicScore());

    return 0;
}
