#include <iostream>
#include <sstream>
#include <istream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

int should_exit = 0;

namespace Backend {
    std::map<std::string, double> variables;
    std::map<std::string, std::string> functions;

    std::map<std::string, int> operators = {
        {"+", 1}, {"-", 2}, {"/", 3}, {"*", 4},
        {"sqrt", 5}, {"pow", 6}, {"%", 7}
    };

    void VarDef(std::string name, int value) {
        variables[name] = value;
        std::cout << "'" << name << "' is equal to " << value;
        return;
    }

    void FuncDef(std::string name, std::string data[3]) {
        std::string function = data[0];
        function.append(" ");
        function.append(data[1]);
        function.append(" ");
        function.append(data[2]);
        functions[name] = function;
        std::cout << "function '" << data[0] << "' is:\n" << functions[name] << std::endl;
        return;
    }

    double Eval(std::string in) {
        std::istringstream ss(in);
        std::vector<std::string> v;
        std::string s;

        while(std::getline(ss, s, ' ')) {
            v.push_back(s);
        }

        if(v[0] == "$") {
            VarDef(v[1], std::stoi(v[2]));
            return 0;
        }

        if(v[0] == "def") {
            std::string data[3] = {v[2], v[3], v[4]};
            FuncDef(v[1], data);
            return 1;
        }

        if(v[0] == "run") {
            return Eval(functions[v[1]]);
        }

        if(v[0] == "puts") {
            return variables[v[1]];
        }

        if(v[0] == "input") {
            std::string data;
            std::getline(std::cin, data);
            variables[v[1]] = std::stod(data);
            return 1;
        }

        double x = 0, y = 0;

        try {
            x = std::stod(v[1]);
        } catch(const std::invalid_argument& e) {
            x = variables[v[1]];
        }
        y = std::stod(v[2]);

        if(v[0] == "if") {
            if(x == y) {
                std::string recursion = "";
                recursion.append(v[3]);
                recursion.append(" ");
                recursion.append(v[4]);
                recursion.append(" ");
                recursion.append(v[5]);
                return Eval(recursion);
            }
            else {
                return 0;
            }
        }

        double res;

        switch(operators[v[0]]) {
            case 1:
                res = x+y;
                break;

            case 2:
                res = x-y;
                break;
            
            case 3:
                res = x/y;
                break;
            
            case 4:
                res = x*y;
                break;
            
            case 5:
                res = std::sqrt(x);
                break;
            
            case 6:
                res = std::pow(x, y);
                break;
            
            case 7:
                res = (double)((int)x % (int)y);
                break;
        }

        return res;
    }
}