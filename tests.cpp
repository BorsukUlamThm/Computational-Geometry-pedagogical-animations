#include <iostream>
#include <filesystem>
#include "Graphics/Model/Global_variables.h"

namespace fs = std::filesystem;

std::vector<std::string> split_line(std::string& line)
{
    std::istringstream iss(line);
    std::vector<std::string> res;
    std::string word;

    while(!iss.eof())
    {
        iss >> word;
        res.push_back(word);
    }

    return res;
}

int main()
{
    std::ifstream is ("../test");
    std::string line;
    std::getline(is, line);

    for(;!is.eof(); std::getline(is, line))
    {
        auto words = split_line(line);
        std::cout << words.size();
    }

}