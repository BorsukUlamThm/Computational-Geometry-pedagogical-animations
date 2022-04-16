#ifndef ALPHA_FILE_MANAGEMENT_H
#define ALPHA_FILE_MANAGEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>


namespace gt
{
/// Project name
#define PROJECT_NAME "Computational-Geometry-pedagogical-animations"

std::filesystem::path get_project_directory()
{
    std::filesystem::path current_dir = std::filesystem::current_path();

    while (current_dir.filename().string() != PROJECT_NAME)
    {
        if (current_dir.parent_path() == current_dir.root_directory())
        {
            std::cerr << "Warning : Executable is not executed from " << PROJECT_NAME
                      << " directory" << std::endl
                      << "          Some graphics may not work properly" << std::endl;

            return std::filesystem::path();
        }
        current_dir = current_dir.parent_path();
    }

    return current_dir;
}

std::filesystem::path get_config_directory()
{
    std::filesystem::path Project_dir = get_project_directory();

    if (Project_dir.empty())
    {
        return Project_dir;
    }

    return Project_dir / ".config";
}

std::vector<std::string> split_line(std::string& line)
{
    std::istringstream iss(line);
    std::vector<std::string> res;
    std::string word;

    while (!iss.eof())
    {
        iss >> word;
        res.push_back(word);
    }

    return res;
}
}


#endif //ALPHA_FILE_MANAGEMENT_H
