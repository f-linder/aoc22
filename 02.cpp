#include <algorithm>
#include "parser.h"
#include <unordered_map>

enum class Shape { Rock, Paper, Scissors };

struct Tournament {

    std::vector<std::pair<char, char>> rounds;
    std::unordered_map<char, Shape> charToShape; 

    Tournament(std::string filename) {
        charToShape = {{'A', Shape::Rock}, {'B', Shape::Paper}, {'C', Shape::Scissors},
                        {'X', Shape::Rock}, {'Y', Shape::Paper}, {'Z', Shape::Scissors}};

        auto lines = Parser::readLines(filename);
        for (const auto & l : lines) {
            if (l.size() < 3) continue;
            rounds.push_back({l.at(0), l.at(2)});
        }
    }
    
    static Shape winningShape(Shape elf) {
        if (elf == Shape::Rock)         return Shape::Paper;
        if (elf == Shape::Paper)        return Shape::Scissors;
        if (elf == Shape::Scissors)     return Shape::Rock;
    }

    static Shape losingShape(Shape elf) {
        if (elf == Shape::Rock)         return Shape::Scissors;
        if (elf == Shape::Paper)        return Shape::Rock;
        if (elf == Shape::Scissors)     return Shape::Paper;
    }

    static int points(Shape elf, Shape me) {
        int result{0};
        
        switch (me) {
            case Shape::Rock:       result += 1; break;
            case Shape::Paper:      result += 2; break;
            case Shape::Scissors:   result += 3; break;
             
        }
        
        // draw
        if (elf == me)                  result += 3;
        // win
        if (me == winningShape(elf))    result += 6;

        return result;
    }


    int calculateScore(bool part2 = false) {
        int score{0};
        
        for (const auto & [elf, me] : rounds) {
            Shape elfsShape = charToShape[elf];
            Shape myShape = charToShape[me];

            if (part2) {
                switch (me) {
                    case 'X': myShape = losingShape(elfsShape);     break;
                    case 'Y': myShape = elfsShape;                  break;
                    case 'Z': myShape = winningShape(elfsShape);    break;
                }
            }

            score += points(elfsShape, myShape);
        }

        return score;
    }
};




int main() {
    fmt::print("AOC-22 #02\n");
    Tournament t = {"../data/02.txt"};

    fmt::print("overall score: {}\n", t.calculateScore());
    fmt::print("updated score: {}\n", t.calculateScore(true));
    return 0;
}
