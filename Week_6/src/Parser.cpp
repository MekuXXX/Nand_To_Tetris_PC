#include "Parser.hpp"

Parser::Parser(const std::string &path): line_number(0)
{
    if (!fs::exists(path))
    {
        std::runtime_error("File is not found");
    }

    this->file.open(path);
    if (this->file.fail())
    {
        throw std::runtime_error("Error happen when trying to open the file");
    }

    this->advance();
}

Parser::~Parser()
{
    this->file.close();
}

void Parser::advance() 
{
    while (std::getline(this->file, this->line)) 
    {
        this->cleanLine();
        if (!this->line.empty()) 
        {
            this->line_number += 1;
            return;
        }
    }
}

void Parser::cleanLine()
{
    size_t commentPos = this->line.find("//");
    if (commentPos != std::string::npos)
    {
        this->line.erase(commentPos);
    }

    this->line = StringUtils::trim(this->line);
}

bool Parser::hasMoreCommands()
{
    return !this->file.eof(); 
}

COMMAND_TYPE Parser::commandType() 
{
    if (this->line.starts_with("@"))
    {
        return COMMAND_TYPE::A_COMMAND;
    }
    else if (this->line.starts_with("("))
    {
        return COMMAND_TYPE::S_COMMAND;
    }
    else 
    {
        return COMMAND_TYPE::C_COMMAND;
    }
}

bool Parser::commandValid(const std::vector<COMMAND_TYPE> &types)
{
    for (auto& type: types)
    {
        if (this->commandType() == type) return true;
    }

    return false;
}

std::string Parser::symbol()
{
    COMMAND_TYPE type = this->commandType();
    std::string result = "";

    if (type == COMMAND_TYPE::A_COMMAND) 
    {
        result = this->line.substr(1);
    }
    else if (type == COMMAND_TYPE::S_COMMAND)
    {
        result = this->line.substr(1, this->line.find(')') - 1);
    }
    else 
    {
        throw std::runtime_error("Must be called in A or S commands");
    }

    return result;
}

std::string Parser::destination()
{
    if (!this->commandValid(std::vector<COMMAND_TYPE> { COMMAND_TYPE::C_COMMAND }))
    {
        throw std::runtime_error("Command must be C command");
    }

    if (this->line.find('=') == std::string::npos)
    {
        return "";
    }

    return this->line.substr(0, this->line.find('='));
}

std::string Parser::computation()
{
    if (!this->commandValid(std::vector<COMMAND_TYPE> { COMMAND_TYPE::C_COMMAND }))
    {
        throw std::runtime_error("Command must be C command");
    }

    size_t start = 0;
    size_t equalIndex = this->line.find('=');
    if (equalIndex != std::string::npos)
    {
        start = equalIndex + 1;
    }

    return this->line.substr(start, this->line.find(';') - equalIndex - 1);
}


std::string Parser::jump()
{
    if (!this->commandValid(std::vector<COMMAND_TYPE> { COMMAND_TYPE::C_COMMAND }))
    {
        throw std::runtime_error("Command must be C command");
    }

    size_t start = this->line.find(';');

    if (start == std::string::npos)
    {
        return "";
    }

    start += 1;

    if (start == this->line.size() - 1)
    {
        throw std::runtime_error("Must add valid jump statement");
    }


    // return this->line.substr(start, 3);
    return this->line.substr(start, this->line.find('\n')); // To make it dynamic if we want change the number of jump commands
}