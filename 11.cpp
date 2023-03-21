#include "parser.h"
#include <functional>
#include <stdexcept>

struct Monkey {
    std::vector<long long> items;
    std::function<long long (long long)> operation;
    std::function<bool (long long)> test;
    int modulus;
    int monkeyTrue;
    int monkeyFalse;
    long long activity{0};
};

class MonkeyGame {
    std::vector<Monkey> monkeys;
    long long lcm;

public:
    MonkeyGame(std::string filename) : lcm{1} {
        auto lines = Parser::readLines(filename);
        Monkey m;

        for (const auto & l : lines) {
            if (l.empty()) continue;

            if (l.starts_with("  Starting items")) {
                auto items = Parser::readInts(l.substr(17), ',');
                for (auto i : items)
                    m.items.push_back(i); 
            }
            if (l.starts_with("  Operation")) {
                auto words = Parser::readStrings(l, ' ');
                char op = words[4][0];
                std::string operand = words[5];

                switch (op) {
                    case '+':
                        if (operand == "old")
                            m.operation = [] (auto old) { return old + old; };
                        else 
                            m.operation = [operand] (auto old) { return old + std::stoi(operand); };
                        break;
                    case '*':
                        if (operand == "old")
                            m.operation = [] (auto old) { return old * old; };
                        else 
                            m.operation = [operand] (auto old) { return old * std::stoi(operand); };
                        break;
                    default:
                        throw std::logic_error("operation not in [+, *]");
                } 
            }
            if (l.starts_with("  Test")) {
                auto words = Parser::readStrings(l, ' ');
                int mod = std::stoi(words[3]);
                lcm *= mod;
                m.modulus = mod;
                m.test = [mod] (auto lvl) { return (lvl % mod == 0); };
            }
            if (l.starts_with("    If true")) {
                auto words = Parser::readStrings(l, ' ');
                m.monkeyTrue = std::stoi(words[5]);
            }
            if (l.starts_with("    If false")) {
                auto words = Parser::readStrings(l, ' ');
                m.monkeyFalse = std::stoi(words[5]);
                // create new monkey
                monkeys.emplace_back(m);
                m = {};
            }
        }
    }

    void playRound(bool div3) {
        for (auto & m : monkeys) {
            for (auto & item : m.items) {
                item = m.operation(item);
                if (div3)
                    item /= 3;

                // does not change outcome of test 
                item %= lcm;

                if (m.test(item))
                    monkeys[m.monkeyTrue].items.push_back(item);
                else
                    monkeys[m.monkeyFalse].items.push_back(item);
            }

            m.activity += m.items.size();
            m.items.clear();
        } 
    }

    long long monkeyBusiness(int rounds, bool div3 = true) {
        for (int i = 0; i < rounds; ++i)
            playRound(div3); 
        
        std::vector<long long> activities;
        for (const auto & m : monkeys) {
            activities.push_back(m.activity);
        }
        std::sort(activities.begin(), activities.end(), [] (auto a, auto b) { return a > b; });

        if (activities.size() < 2) throw std::logic_error("not enough monkeys");

        return activities[0] * activities[1];
    }
};

int main() {
    fmt::print("AOC-22 #11\n");
   
    MonkeyGame mg1 = {"../data/11.txt"};
    int part1 = 20;
    fmt::print("monkey business after playing {} rounds: {}\n", part1, mg1.monkeyBusiness(part1));
    
    MonkeyGame mg2 = {"../data/11.txt"};
    int part2 = 10000;
    fmt::print("monkey business after playing {} rounds: {}\n", part2, mg2.monkeyBusiness(part2, false));

    return 0;
}
