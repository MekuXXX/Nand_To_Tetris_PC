#pragma once
#include <string>
#include <algorithm>


namespace StringUtils 
{
    std::string& ltrim(std::string& str);
    std::string& rtrim(std::string& str);
    std::string& trim(std::string& str);
}