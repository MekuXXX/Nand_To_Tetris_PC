#pragma once
#include <string>
#include <unordered_map>
#include <stdexcept>

class Code 
{
    public:
        Code();
        std::string destination(const std::string &dest);
        std::string computation(const std::string &comp);
        std::string jump(const std::string &jump);

    private:
        std::unordered_map<std::string, std::string> destTable;
        std::unordered_map<std::string, std::string> compTable;
        std::unordered_map<std::string, std::string> jumpTable;
};