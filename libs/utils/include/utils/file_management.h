#pragma once

#include <string>
#include <vector>
#include <filesystem>


namespace utils
{
	namespace fs = std::filesystem;

	/// Project name
	constexpr char PROJECT_NAME[] =
			"Computational-Geometry-pedagogical-animations";

	/*!
	 * @return the root of the project directory
	 */
	fs::path get_project_directory();

	/*!
	 * @return the root of the data directory
	 */
	fs::path get_data_directory();

	/*!
	 * @return the root of the .config directory
	 */
	fs::path get_config_directory();

	/*!
	 * @return the list of the words separated by whitespaces
	 */
	std::vector<std::string> split_line(const std::string& line);
}