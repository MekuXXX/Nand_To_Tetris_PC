#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include "StringUtils.hpp"

namespace fs = std::filesystem;

enum class COMMAND_TYPE 
{
    A_COMMAND,
    C_COMMAND,
    S_COMMAND
};

class Parser 
{
    public:
        Parser(const std::string &path);
        ~Parser();

        bool hasMoreCommands();
        COMMAND_TYPE  commandType();
        std::string symbol();
        std::string destination();
        std::string computation();
        std::string jump();
        void  advance();


    private:
        std::ifstream file;
        std::string line;
        int line_number;

        void cleanLine();
        bool commandValid(const std::vector<COMMAND_TYPE> &types);
};