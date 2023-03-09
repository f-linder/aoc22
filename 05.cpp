#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>
#include <fmt/core.h>
#include "parser.h"
#include <utility>
#include <stack>
#include <vector>

struct Crane {
    int count;
    int from;
    int to;
};

class CrateStacks {
    std::vector<std::vector<char>> stacks;
    std::vector<Crane> instructions;
public:
    CrateStacks(std::string filename) {
        std::vector<std::vector<char>> initialAllocation =  {
            {'T', 'D', 'W', 'Z', 'V', 'P'},
            {'L', 'S', 'W', 'V', 'F', 'J', 'D'},
            {'Z', 'M', 'L', 'S', 'V', 'T', 'B', 'H'},
            {'R', 'S', 'J'},
            {'C', 'Z', 'B', 'G', 'F', 'M', 'L', 'W'},
            {'Q', 'W', 'V', 'H', 'Z', 'R', 'G', 'B'},
            {'V', 'J', 'P', 'C', 'B', 'D', 'N'},
            {'P', 'T', 'B', 'Q'},
            {'H', 'G', 'Z', 'R', 'C'}   
        };

        for (const auto & st : initialAllocation) {
            std::vector<char> v;
            for (auto ch : st) 
                v.push_back(ch);
            stacks.push_back(v); 
        }

        auto lines = Parser::readLines(filename);
        for (const auto & l : lines) {
            if (l.empty() || l.at(0) != 'm') continue;

            Crane c;
            // format: move <count> from <from> to <to>
            auto strings = Parser::readStrings(l, ' ');
            c.count = std::stoi(strings[1]);
            c.from = std::stoi(strings[3]) - 1;
            c.to = std::stoi(strings[5]) - 1;

            instructions.push_back(c);
        } 
    }

    std::string rearrange9000() {
        for (auto c : instructions) {
            if (c.count > stacks[c.from].size()) 
                throw std::logic_error("stack does not have that much elements");

            for (int i = 0; i < c.count; ++i) {
                stacks[c.to].push_back(stacks[c.from].back());
                stacks[c.from].pop_back();
            }
        }

        std::string topElements{""};
        for (const auto & st : stacks) {
            if (st.empty()) continue;
            topElements += st.back();
        }

        return topElements;
    }

    std::string rearrage9001() {
        for (auto c : instructions) {
            if (c.count > stacks[c.from].size())
                throw std::logic_error("stack does not have that much elements");

            std::vector<char> temp;
            for (int i = 0; i < c.count; ++i) {
                temp.push_back(stacks[c.from].back());
                stacks[c.from].pop_back();
            } 
            for (int i = 0; i < c.count; ++i) {
                stacks[c.to].push_back(temp.back());
                temp.pop_back();
            } 
        }

        std::string topElements{""};
        for (const auto & st : stacks) {
            if (st.empty()) continue;
            topElements += st.back();
        }

        return topElements;
    }
};

int main() {
    fmt::print("AOC-22 #05\n");
    
    CrateStacks cs = {"../data/05.txt"};
    fmt::print("Elements at the top of the stack with Crane9001: {}\n", cs.rearrage9001());
    return 0;
}
