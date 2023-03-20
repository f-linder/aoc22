#include "parser.h"
#include <cmath>
#include <stdexcept>

enum class Operation { NOOP, ADD };

class CRT {
    std::vector<std::pair<Operation, int>> instructions;
    std::vector<int> registerX;

public:
    CRT(std::string filename) {
        auto lines = Parser::readLines(filename);
        for (const auto & l : lines) {
            if (l.empty()) continue;
            
            auto words = Parser::readStrings(l, ' ');

            if (words.size() == 1 && words[0] == "noop") 
                instructions.emplace_back(Operation::NOOP, 0);
            else if (words.size() == 2 && words[0] == "addx")
                instructions.emplace_back(Operation::ADD, std::stoi(words[1]));
            else
                throw std::invalid_argument("instruction not recognized");
        } 
        registerX.push_back(1);
    }

    void execute() {
        int val{1};

        for (const auto & [op, x] : instructions) {
            switch (op) {
                case Operation::NOOP:
                    registerX.push_back(val);
                    break;
                case Operation::ADD:
                    registerX.push_back(val);
                    registerX.push_back(val);
                    val += x;
                    break;
                default: 
                    break;
            }
        }
    }

    int sumSignalStrengths(int max) {
        if (registerX.size() < max) throw std::logic_error("too little cycles");

        std::vector<int> interesingCycles;
        for (int i = 20; i <= max; i += 40)
            interesingCycles.push_back(i);

        int sum{0};
        for (auto i : interesingCycles)
            sum += i * registerX[i];

        return sum;
    }

    void print() {
        if (registerX.size() <= 240) throw std::logic_error("too little cycles");

        for (int i = 0; i < 240; ++i) {
            if (i % 40 == 0) 
                fmt::print("\n");

            int posSprite = registerX[i + 1];
            // one pixel apart or on the same spot
            if (std::abs(posSprite - (i % 40)) <= 1)
                fmt::print("#");
            else
                fmt::print(".");
        }
    }
};

int main() {
    fmt::print("AOC-22 #10\n");
    
    CRT crt = {"../data/10.txt"};
    crt.execute();

    fmt::print("sum of important signal strengths after 220 cycles: {}\n", crt.sumSignalStrengths(220));
    crt.print();

    return 0;
}
