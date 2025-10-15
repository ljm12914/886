#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <CLI/CLI.hpp>

namespace Boot {
    typedef uint8_t u8;
    using std::string, std::filesystem::path, std::filesystem::absolute, std::filesystem::exists, std::error_code, std::cout, std::cerr, std::endl, CLI::App, CLI::CallForHelp, CLI::CallForVersion, CLI::ParseError;

    enum struct ArgType : u8 {
        None, Path, Infix
    };

    inline ArgType processArguments(int argc, char* argv[], string& either) {
        App app;
        app.set_config();
        app.set_help_all_flag();
        app.set_version_flag("-v,--version", "1.0.0", "Display program version information and exit.");
        app.set_help_flag("-h,--help", "Show this help message and exit.");
        string filePathStr, infixStr;
        auto fileOption = app.add_option("-f,--file", filePathStr, "Run an input file.");
        auto infixOption = app.add_option("-x,--infix", infixStr, "Run a constant infix expression.");
        fileOption->excludes(infixOption);
        try { app.parse(argc, argv); }
        catch(const CallForHelp& e) {
            cout << app.help() << endl;
            exit(e.get_exit_code());
        }
        catch(const CallForVersion& e) {
            cout << e.what() << endl;
            exit(e.get_exit_code());
        }
        catch(const ParseError& e) {
            cerr << e.what() << endl;
            exit(e.get_exit_code());
        }
        if (filePathStr.empty()) {
            if(!infixStr.empty()) {
                either = infixStr;
                return ArgType::Infix;
            }
            else return ArgType::None;
        }
        else {
            error_code ec;
            path filePath = absolute(filePathStr, ec);
            if (ec) {
                cerr << "File " << filePathStr << " could not be resolved: " << ec.message() << endl;
                exit(1001);
            }
            filePath = filePath.lexically_normal();
            filePath.make_preferred();
            if (!exists(filePath)) {
                cerr << "File " << filePath.string() << " does not exist." << endl;
                exit(1002);
            }
            either = filePath.string();
            return ArgType::Path;
        }
    }
}