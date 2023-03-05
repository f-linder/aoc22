#include <stdexcept>
#include <string>
#include <fmt/core.h>
#include <algorithm>
#include "parser.h"
#include <unordered_map>
#include <vector>

struct Tournament {
    // pair = [elfs shape, our shape]
    std::vector<std::pair<char, char>> pairs;

    Tournament(std::string filename) {
        auto lines = Parser::readLines(filename);

        for (const auto & l : lines) {
            if (l.size() < 3) continue;
            pairs.push_back({l.at(0), l.at(2)});
        }
    }
    
    // calculate win/draw/lose for given shapes
    int round1() {
        // rock "X" = 1, paper "Y" = 2, scissors "Z" = 3
        std::unordered_map<char, int> shapeToScore = {{'X', 1}, {'Y', 2}, {'Z', 3}};
        int score = 0;

        for (const auto & [elf, me] : pairs) {
            score += shapeToScore[me]; 

            switch (elf) {
                // rock
                case 'A': 
                    if (me == 'X') score += 3;
                    else if (me == 'Y') score += 6;
                    else score += 0;
                    break;
                // paper
                case 'B':
                    if (me == 'X') score += 0;
                    else if (me == 'Y') score += 3;
                    else score += 6;
                    break;
                // scissors
                case 'C':
                    if (me == 'X') score += 6;
                    else if (me == 'Y') score += 0;
                    else score += 3;
                    break;
         
                default: throw std::logic_error("wrong type");
            }
        }
        return score;
    }

    // calculate the shape we chose for given win/draw/lose
    int round2() {
        int score = 0;

        for (const auto & [elf, result] : pairs) {
            switch (result) {
                // loose
                case 'X':
                    score += 0;
                    // rock -> scissor +2
                    if (elf == 'A') score += 3;
                    // paper -> rock +1
                    else if (elf == 'B') score += 1;
                    // scissors -> paper
                    else score += 2;
                    break;
                // draw
                case 'Y':
                    score += 3;
                    if (elf == 'A') score += 1;
                    else if (elf == 'B') score += 2;
                    else score += 3;
                    break;
                // win
                case 'Z':
                    score += 6;
                    if (elf == 'A') score += 2;
                    else if (elf == 'B') score += 3;
                    else score += 1;
                    break;
            }
        }

        return score;
    }
};




int main() {
    fmt::print("AOC-22 #02\n");
    Tournament t = {"../data/02.txt"};

    fmt::print("overall score: {}\n", t.round1());
    fmt::print("update score: {}\n", t.round2());
    return 0;
}
