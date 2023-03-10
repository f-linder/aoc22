#include <cctype>
#include "parser.h"

struct Comparments {
    std::string left;
    std::string right;
};

class Rucksack {
    std::vector<Comparments> compartments;

public:
    Rucksack(std::string filename) {
        auto lines = Parser::readLines(filename);
        for (const auto & l : lines) {
            if (l.empty()) continue;
            size_t len = l.size();
            compartments.push_back({l.substr(0, len / 2), l.substr(len / 2)});
        }
        
    }
    
    int priority(char c) {
        // lowercase, 1-26
        if (islower(c)) return c - 'a' + 1;
        // uppercase, 27-52
        if (isupper(c)) return c - 'A' + 27; 
        return 0;
    }

    int sumPriorities() {
        int sum{0};
        for (const auto & cmp : compartments) {
            if (cmp.left.size() != cmp.right.size()) throw std::logic_error("comparments not same size");
            
            for (const auto & c : cmp.left) {
                if (cmp.right.find(c) != std::string::npos) {
                    sum += priority(c);
                    break;
                }
            }
        }
        return sum;
    }

    int badgeSum() {
        int sum{0};
        if (compartments.size() % 3 != 0) throw std::logic_error("compartments not divisible by 3");

        for (size_t i = 0; i < compartments.size(); i += 3) {
            const auto a = compartments.at(i).left + compartments.at(i).right;
            const auto b = compartments.at(i + 1).left + compartments.at(i + 1).right;
            const auto c = compartments.at(i + 2).left + compartments.at(i + 2).right;

            for (const auto & character : a) {
                if (b.find(character) != std::string::npos && c.find(character) != std::string::npos) {
                    sum += priority(character);
                    break;
                }
            }
        }
        return sum;
    }
};

int main() {
    fmt::print("AOC-22 #03\n");

    Rucksack r{"../data/03.txt"};
    fmt::print("sum of priorities: {}\n", r.sumPriorities());
    fmt::print("sum of badge priorities: {}\n", r.badgeSum());

    return 0;
}
