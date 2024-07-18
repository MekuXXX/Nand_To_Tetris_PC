#pragma once
#include <string>
#include <bitset>
#include <unordered_map>
#include <cctype>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include "Parser.hpp"
#include "Code.hpp"

class Assembler 
{
    public:
        Assembler(const std::string &path, const std::string &out);
        // Assembler(const std::string &path);
        void readSymbols();
        bool assemble();

    private:
        std::unordered_map<std::string, int> table;
        std::string path;
        std::string output;
        Parser parser;
        Code code;

        static bool isSymbol(const std::string &str);
        static std::string getPathWithoutExtension(const std::string &filePath);
};