#include <iostream>
#include <istream>
#include <fstream>
#include <string>

#include "backend.hh"
#include "defines.h"

int ParseFile(std::string where) {
    std::ifstream input(where);

    for(std::string line; std::getline(input, line);) {
        Backend::Eval(line);
    }

    return 0;
}

int main(int argc, char const *argv[]) {
    if(argc > 1) {
        return ParseFile(argv[1]);
    }
    std::cout << "Rock " << VERSION << std::endl;
    std::cout << "Copyright Ellie Putnam, 2024. All rights reserved" << std::endl;
    std::cout << "This program is distrubuted without any warranty" << std::endl;
    while(!should_exit) {
        std::string out;
        std::string command = "";
        std::cout << "> ";
        std::getline(std::cin, command);
        if(command == "exit") {
            should_exit = 1;
            return 0;
        }
        std::cout << std::to_string(Backend::Eval(command)) << std::endl;
    }
    return 0;
}