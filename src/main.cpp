#include <chrono>
#include <filesystem>
#include <string>

#include "InfixParser/InfixParser.hpp"
#include "boot.hpp"

using std::cout, std::cin, std::getline, std::endl, std::setprecision, std::filesystem::path, std::string, std::chrono::steady_clock, std::chrono::duration_cast, std::chrono::microseconds;

namespace Main {
    static void hold() noexcept {
        string input;
        while (true) {
            cout << "886> ";
            getline(cin, input);
            cout << input << endl;
        }
    }

    static void exit() noexcept {
        
    }
}

int main(int argc, char** argv) {
    string arg;
    switch (Boot::processArguments(argc, argv, arg)) {
        case Boot::ArgType::Path: {
            path filePath(arg);
            //todo: run file
            break;
        }
        case Boot::ArgType::Infix: {
            steady_clock::time_point start = steady_clock::now();
            InfixParser::Expression expr;
            if (!InfixParser::parseInfixExpression(arg, expr)) {
                cout << "Failed to parse expression: " << InfixParser::getErrorMessage() << endl;
                return 1;
            }
            double result = 0;
            if(!InfixParser::calculateInfixExpression(expr, result)) {
                cout << "Failed to calculate expression: " << InfixParser::getErrorMessage() << endl;
                return 1;
            }
            steady_clock::time_point end = steady_clock::now();
            cout << setprecision(15) << result << "\nCalculated in " << duration_cast<microseconds>(end - start).count() << "us" << endl;
            break;
        }
        case Boot::ArgType::None: {
            //todo: REPL
            cout << "REPL mode" << endl;
            Main::hold();
            break;
        }
    }
    return 0;
}