#include <array>
#include <algorithm>
#include "parser.h"

class Detector {
    std::string_view input;
    std::vector<char> lastChars;

public:
    Detector(std::string filename) {
        auto lines = Parser::readLines(filename);
        if (lines.size() != 1) throw std::logic_error("input consists not of one string");
        
        input = lines[0];
    }

    bool noDuplicates() {
        std::sort(lastChars.begin(), lastChars.end());
        for (size_t i = 0; i < lastChars.size() - 1; ++i) {
            if (lastChars[i] == lastChars[i + 1]) return false;
        }
        return true;
    }

    int startOfN(int n) {
        if (input.size() < n) throw std::logic_error("string consists of < 4 characters");

        for (size_t i = n; i < input.length(); ++i) {
            lastChars = {input.begin() + i - n, input.begin() + i};
            if (noDuplicates()) return i;
        }
        throw std::logic_error("no starting point found");
    }
};

int main() {
    fmt::print("AOC-22 #06\n");
    
    Detector d = {"../data/06.txt"};

    int packet = 4;
    int message = 14;
    fmt::print("start-of-packet marker found after: {} characters\n", d.startOfN(packet));
    fmt::print("start-of-message marker found after: {} characters\n", d.startOfN(message));

    return 0;
}
