#pragma once

#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <fmt/core.h>
#include <sstream>

class Parser {
public:
    // open file "filename" and return vector of strings representing each line of file
    static std::vector<std::string> readLines(std::string fileName);
    // parse delimiter seperated ints from given string
    static std::vector<int> readInts(std::string filename, char deliminiter);

};



std::vector<std::string> Parser::readLines(std::string fileName) {
    std::ifstream input{fileName};
    if(!input.is_open()) {
        throw std::invalid_argument(fmt::format("error opening file{}", fileName));
    }
    
    std::vector<std::string> lines;
    std::string line;

    while(std::getline(input, line)) {
        lines.emplace_back(line);
    }

    fmt::print("read {} lines from {}\n", lines.size(), fileName);
    return lines;
}

std::vector<int> readInts(const std::string& string, char delimiter) {
    std::vector<int> items;
    std::string item;
    std::stringstream ss(string);

    while(std::getline(ss, item, delimiter)) {
        if (item.empty()) continue;
        items.push_back(std::stoi(item));
    }

    return items;
}









