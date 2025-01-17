#include "Code.hpp"

Code::Code() {
    // Initialize destination table
    this->destTable = {
        {"", "000"},
        {"M", "001"},
        {"D", "010"},
        {"MD", "011"},
        {"A", "100"},
        {"AM", "101"},
        {"AD", "110"},
        {"AMD", "111"}
    };

    // Initialize computation table
    this->compTable = {
        {"0", "101010"},
        {"1", "111111"},
        {"-1", "111010"},
        {"D", "001100"},
        {"A", "110000"},
        {"M", "110000"},
        {"!D", "001101"},
        {"!A", "110001"},
        {"!M", "110001"},
        {"-D", "001111"},
        {"-A", "110011"},
        {"-M", "110011"},
        {"D+1", "011111"},
        {"A+1", "110111"},
        {"M+1", "110111"},
        {"D-1", "001110"},
        {"A-1", "110010"},
        {"M-1", "110010"},
        {"D+A", "000010"},
        {"D+M", "000010"},
        {"D-A", "010011"},
        {"D-M", "010011"},
        {"A-D", "000111"},
        {"M-D", "000111"},
        {"D&A", "000000"},
        {"D&M", "000000"},
        {"D|A", "010101"},
        {"D|M", "010101"},
    };

    // Initialize jump table
    this->jumpTable = {
        {"", "000"},
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"}
    };
}

std::string Code::destination(const std::string &dest) {
    auto it = this->destTable.find(dest);
    if (it != this->destTable.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Invalid destination: " + dest);
    }
}

std::string Code::computation(const std::string &comp) {
    auto it = this->compTable.find(comp);
    if (it != this->compTable.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Invalid computation: " + comp);
    }
}

std::string Code::jump(const std::string &jump) {
    auto it = this->jumpTable.find(jump);
    if (it != this->jumpTable.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Invalid jump: " + jump);
    }
}
