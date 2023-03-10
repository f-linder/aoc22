#include <algorithm>
#include "parser.h"

class Calories {
    std::vector<int> sums;

    public:
    Calories(std::string filename) {
        auto lines = Parser::readLines(filename);
        int current_kcal{0};
        
        for (const auto & line : lines) {
           if (line.empty()) {
                sums.emplace_back(current_kcal);
                current_kcal = 0;
                continue;
            } 
            current_kcal += std::stoi(line);
        }
    }

    int getMax() {
        auto max = std::max_element(sums.begin(), sums.end());
        return *max;
    }

    int getTop3 () {
        std::sort(sums.begin(), sums.end(), [] (int a, int b) { return a > b; });
        
        if (sums.size() < 3) 
            throw std::logic_error("There are fewer than 3 elfs");

        return sums[0] + sums[1] + sums[2];
    }
};

int main() {

    fmt::print("AOC-22 #01\n");
    Calories kcal{"../data/01.txt"};
    fmt::print("maximum sum of kcal: {}\n", kcal.getMax());
    fmt::print("sum of top three elfs: {}\n", kcal.getTop3());

    return 0; 
}
