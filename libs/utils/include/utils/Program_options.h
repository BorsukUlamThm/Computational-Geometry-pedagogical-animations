#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>


namespace utils
{
	struct Option
	{
		std::string name;
		std::string short_name;
		bool is_used = false;
		std::vector<std::string> parameters;

		Option() = default;
		Option(const std::string& name,
			   const std::string& short_name);
	};

	class Program_options
	{
	private:
		std::vector<Option> options;

	public:
		Program_options() = default;
		~Program_options() = default;

		Option& operator[](unsigned i);
		const Option& operator[](unsigned i) const;

		void add_option(const std::string& name,
						const std::string& short_name);
		void parse_command_line(int argc, char** argv);

	private:
		unsigned option_index(const std::string& parsed_name);
	};
}