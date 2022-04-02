#include <iostream>
#include <filesystem>
#include "Graphics/Model/Global_variables.h"

namespace fs = std::filesystem;

void print(unsigned n)
{
    std::vector<unsigned> numbers;
    while(n >= 1000)
    {
        numbers.push_back(n % 1000);
        n = n / 1000;
    }
    numbers.push_back(n);

    std::string title;
    title += std::to_string(numbers[numbers.size() - 1]);
    for(unsigned i = numbers.size() - 2; i != -1; --i)
    {
        title += " ";
        if(numbers[i] < 100)
        {
            title += "0";
        }
        if(numbers[i] < 10)
        {
            title += "0";
        }
        title += std::to_string(numbers[i]);
    }
    std::cout << title << std::endl;
}

int main()
{
    print(2008);

}