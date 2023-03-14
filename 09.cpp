#include "parser.h"
#include <cmath>
#include <stdexcept>
#include <string>
#include <set>
#include <array>

enum class Direction { Right, Left, Up, Down };

struct Motion { 
    Direction dir;
    int count;
};

class RopeBridge {
    std::vector<Motion> movement;    

public:
    RopeBridge(std::string filename) {
        auto lines = Parser::readLines(filename);

        for (const auto & l : lines) {
            auto m = Parser::readStrings(l, ' ');
            if (m.size() != 2) throw std::invalid_argument("motion not recognized");
            
            Motion motion;
            motion.count = std::stoi(m[1]);

            if (m[0] == "R") motion.dir = Direction::Right;
            if (m[0] == "L") motion.dir = Direction::Left;
            if (m[0] == "U") motion.dir = Direction::Up;
            if (m[0] == "D") motion.dir = Direction::Down;

            movement.emplace_back(motion);
        }
    }
    
    void updatePosition(std::pair<int, int> & head, std::pair<int, int> & tail) {
        int dx = tail.first - head.first;
        int dy = tail.second - head.second;
       
        // no need to move
        if (std::abs(dx) <= 1 && std::abs(dy) <= 1) return;
        
        // move straight
        if (std::abs(dx) == 2 && dy == 0) {
            if (dx < 0) tail.first++;
            else        tail.first--;
            return;
        }
        if (std::abs(dy) == 2 && dx == 0) {
            if (dy < 0) tail.second++;
            else        tail.second--;
            return;
        }

        // move diagonally (extra case for (abs(dx) == 2 && abs(dy) == 2) in 2nd part)
        if (dx != 0 && dy != 0 && (std::abs(dx) > 1 || std::abs(dy) > 1)) {
            if (dx < 0) tail.first++; else tail.first--;
            if (dy < 0) tail.second++; else tail.second--;
        }
    }

    int countVisitedPositions(int sizeTail) {
        std::set<std::pair<int, int>> visited{};
        // positions of knots interpreted as (X, Y)
        std::vector<std::pair<int, int>> knots;
        for (int i = 0; i < sizeTail + 1; ++i) knots.emplace_back(std::make_pair(0, 0));
        visited.insert(std::make_pair(0, 0));

        for (auto [dir, count] : movement) {
            for (int i = 0; i < count; ++i) {
                switch (dir) {
                    case Direction::Right:  knots[0].first++; break;
                    case Direction::Left:   knots[0].first--; break;
                    case Direction::Up:     knots[0].second++; break;
                    case Direction::Down:   knots[0].second--; break;
                }

                // update knots in tail
                for (int i = 1; i < knots.size(); ++i) {
                    updatePosition(knots[i - 1], knots[i]);                   
                    if (i == sizeTail) visited.insert(knots[i]);
                }
            }
        }

        return visited.size();
    }

};

int main() {
    fmt::print("AOC-22 #09\n");
    
    RopeBridge rp = {"../data/09.txt"};

    int tail1 = 1;
    int tail2 = 9;

    fmt::print("number of visited positions with tail of size {}: {}\n", tail1, rp.countVisitedPositions(tail1));
    fmt::print("number of visited positions with tail of size {}: {}\n", tail2, rp.countVisitedPositions(tail2));

    return 0;
}
