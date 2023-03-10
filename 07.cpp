#include <algorithm>
#include <map>
#include <utility>
#include "parser.h"

enum class Type { File, Directory };

struct Node {
    std::string name;
    Type type;
    std::map<std::string, Node> content{};
    int size;
    Node* parent;
    // Directory
    Node(std::string n, Node* p) : name{n}, type{Type::Directory}, size{0}, parent{p} {};
    // File
    Node(std::string n, int s, Node* p) : name{n}, type{Type::File}, size{s}, parent{p} {};
};


class DataManager {
    Node root;
    std::vector<Node*> directories{};
    std::vector<std::string> input;

public:
    DataManager(std::string filename) : root("/", nullptr) {
        input = Parser::readLines(filename);
        directories.emplace_back(&root);
        buildTree(); 
    }

    void buildTree() {
        Node* current{&root};

        for (const auto & l : input) {
            if (l.empty() || l == "$ cd /") continue;

            const auto & words = Parser::readStrings(l, ' ');

            // command
            if (words[0] == "$") {
                // list 
                if (words[1] == "ls") continue;
                if (words.size() != 3) throw std::logic_error("invalid command");
                // change directory
                if (words[1] == "cd") {
                    if (words[2] == "..") {
                        if (current->parent == nullptr)
                            throw std::logic_error("can not go up from root directory");
                        else
                            current = current->parent;
                    }
                    else 
                        current = &current->content.at(words[2]);
                    
                }
            }
            // listing of nodes
            else {
                if (words.size() != 2) throw std::logic_error("listing error");
                // directory
                if (words[0] == "dir") {
                    current->content.emplace(std::make_pair(words[1], Node{words[1], current}));
                    directories.emplace_back(&current->content.at(words[1]));
                }
                // file
                else {
                    int size = std::stoi(words[0]);
                    current->content.emplace(words[1], Node{words[1], size, current});
                    // updating size of all directories above
                    Node* t = current;
                    while (t != nullptr) {
                        t->size += size;
                        t = t->parent;
                    }
                }
            }
        }
    }

    int sumDirectories100000() {
        int sum{0};
        for(const auto & d : directories) {
            if (d->size <= 100000) sum += d->size;
        }
        return sum;
    }

    int findSmallestToDelete() {
        int total{70000000};
        int needed{30000000};
        int free = total - root.size;
        int toClean = needed - free;

        std::vector<int> options{};
        for (const auto & n : directories)
            if (n->size >= toClean) options.push_back(n->size);
        std::sort(options.begin(), options.end());
        return options.at(0);
    }
};

int main() {
    fmt::print("AOC-22 #07\n");
    
    DataManager dm = {"../data/07.txt"};

    fmt::print("sum of all directories with <= 100000 size: {}\n", dm.sumDirectories100000());
    fmt::print("size of smallest to directory to free up enough space: {}\n", dm.findSmallestToDelete());

    return 0;
}
