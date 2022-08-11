#pragma once

/** @cond */
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
/** @endcond */


namespace general_tools
{
	namespace fs = std::filesystem;

	/// Project name
#define PROJECT_NAME "Computational-Geometry-pedagogical-animations"

	/*!
	 * @return the root of the project directory
	 */
	fs::path get_project_directory()
	{
		fs::path current_dir = fs::current_path();

		while (current_dir.filename().string() != PROJECT_NAME)
		{
			if (current_dir.parent_path() == current_dir.root_directory())
			{
				std::cerr << "Warning : Executable is not executed from " << PROJECT_NAME
						  << " directory" << std::endl
						  << "          Some graphics may not work properly" << std::endl;

				return {};
			}
			current_dir = current_dir.parent_path();
		}

		return current_dir;
	}

	/*!
	 * @return the root of the .config directory
	 */
	fs::path get_config_directory()
	{
		fs::path res = get_project_directory();

		if (res.empty())
		{
			return res;
		}

		res = res / ".config";

		if (!fs::exists(res))
		{
			std::cerr << "Warning : .config directory not found" << std::endl
					  << "          Some graphics may not work properly" << std::endl;

			return {};
		}

		return res;
	}

	/*!
	 * @param line a parsed line from a config file
	 * @return the list of the words separated by whitespaces
	 */
	std::vector<std::string> split_line(const std::string& line)
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