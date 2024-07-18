#include <iostream>
#include <string>
#include "Assembler.hpp"

int main(int argc, char *argv[])
{
    std::string path = "";
    std::string output = "";

    if (argc < 2)
    {
        std::cout << "Please enter the path or the assembly file: ";
        std::getline(std::cin, path);
    }
    else
    {
        path = argv[1];
    }

    if (argc >= 3)
    {
        output = argv[2];
    }

    std::cout << "Path: " << path << std::endl;
    std::cout << "Output: " << output << std::endl;

    Assembler assembler = Assembler(path, output);
    assembler.assemble();
}
