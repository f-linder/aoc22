#include "parser.h"
#include <utility>

struct Assignment {
    int begin, end;
};

class Cleanup {
    std::vector<std::pair<Assignment, Assignment>> pairs;

public:
    Cleanup(std::string filename) {
        auto lines = Parser::readLines(filename);
        for (const auto & l : lines) {
            if (l.empty()) continue;

            // pair of assignments
            const auto & p = Parser::readStrings(l, ',');
            if (p.size() != 2) continue; 

            // assignment of both elfs
            const auto & a1 = Parser::readInts(p.at(0), '-');
            const auto & a2 = Parser::readInts(p.at(1), '-');
            if (a1.size() != 2 && a2.size() != 2) continue; 
                 
            pairs.push_back(std::make_pair(Assignment{a1.at(0), a1.at(1)}, Assignment{a2.at(0), a2.at(1)}));
        }
    }
    
    // checks whether first contains seconds
    bool contains(Assignment first, Assignment second) {
        return (first.begin <= second.begin && first.end >= second.end);
    }

    int numContainments() {
        int sum{0};
        for (const auto & [a1, a2] : pairs) {
            if (contains(a1, a2) || contains(a2, a1)) sum++;
        }
        return sum;
    }
    
    // first overlaps with second
    bool overlap(Assignment first, Assignment second) {
        return (first.end >= second.begin && first.begin && second.end >= first.begin);
    }

    int numOverlaps() {
        int sum{0};
        for (const auto & [a1, a2] : pairs) {
            if (overlap(a1, a2))  sum++;
        }
        return sum;
    }

};

int main() {
    fmt::print("AOC-22 #04\n");
   
    Cleanup c = {"../data/04.txt"};
    
    fmt::print("number of containments: {}\n", c.numContainments());
    fmt::print("number of overlaps: {}\n", c.numOverlaps());
    return 0;
}
