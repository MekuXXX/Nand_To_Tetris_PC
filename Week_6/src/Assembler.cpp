#include "Assembler.hpp"

Assembler::Assembler(const std::string &path, const std::string &out): path(path), output(out),parser(path), code() 
{

    if (this->output == "")
    {
        this->output = Assembler::getPathWithoutExtension(this->path) + ".hack";
    }
    
    this->table = {
        {"SP", 0},
        {"LCL", 1},
        {"ARG", 2},
        {"THIS", 3},
        {"THAT", 4},
        {"R0", 0},
        {"R1", 1},
        {"R2", 2},
        {"R3", 3},
        {"R4", 4},
        {"R5", 5},
        {"R6", 6},
        {"R7", 7},
        {"R8", 8},
        {"R9", 9},
        {"R10", 10},
        {"R11", 11},
        {"R12", 12},
        {"R13", 13},
        {"R14", 14},
        {"R15", 15},
        {"SCREEN", 16384},
        {"KBD", 24576}
    };

    this->readSymbols();
}

bool Assembler::isSymbol(const std::string &str)
{
    return !std::isdigit(str.at(0));
}

std::string Assembler::getPathWithoutExtension(const std::string &filePath) {
    size_t lastDotPos = filePath.find_last_of('.');
    if (lastDotPos == std::string::npos) {
        return filePath;
    }

    size_t lastSlashPos = filePath.find_last_of("/\\");
    if (lastSlashPos != std::string::npos && lastSlashPos > lastDotPos) {
        return filePath;
    }

    return filePath.substr(0, lastDotPos);
}

void Assembler::readSymbols()
{
    Parser checkSymbols(path);
    std::string symbol = "";
    int line = 0;

    while (checkSymbols.hasMoreCommands())
    {
        if (checkSymbols.commandType() == COMMAND_TYPE::S_COMMAND)
        {
            symbol = checkSymbols.symbol();

            if (!this->table.contains(symbol))
            {
                this->table.insert({ symbol, line });
            }

            checkSymbols.advance();
            continue;
        }

        checkSymbols.advance();
        line += 1;
    }

}


bool Assembler::assemble()
{
    int number_a_command;
    int next_variable_address = 16;
    std::string symbol;
    std::string instruction = "";
    std::string computation = "";
    std::ofstream output_file(this->output);

    if (output_file.fail())
    {
        std::runtime_error("There is error happen when trying open write the output file");
    }

    while (this->parser.hasMoreCommands())
    {
        COMMAND_TYPE command_type = this->parser.commandType();
        if (command_type == COMMAND_TYPE::S_COMMAND)
        {
            this->parser.advance();
            continue;
        }
        else if (command_type  == COMMAND_TYPE::C_COMMAND)
        {
            computation = this->parser.computation();
            instruction = "111";
            
            instruction += computation.find('M') == std::string::npos ? '0' : '1'; 
            instruction += this->code.computation(this->parser.computation()) + this->code.destination(this->parser.destination()) + this->code.jump(this->parser.jump());
            
        }
        else
        {
            instruction = "0";
            symbol = this->parser.symbol();

            if (Assembler::isSymbol(symbol))
            {
                if (this->table.contains(symbol))
                {
                    number_a_command = this->table.at(symbol);
                }
                else 
                {
                    this->table.insert({ symbol, next_variable_address });
                    number_a_command = next_variable_address;
                    next_variable_address += 1;
                }
            }
            else 
            {
                number_a_command = std::stoi(symbol);
            }

            std::bitset<15> bits(number_a_command);
            instruction += bits.to_string();
        }
        

        output_file << instruction << std::endl;
        this->parser.advance();
    }

    output_file.close();
    return true;
}