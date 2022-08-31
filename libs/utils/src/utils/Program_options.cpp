#include "Program_options.h"


namespace utils
{

	Option& Program_options::operator[](unsigned int i)
	{ return options[i]; }

	const Option& Program_options::operator[](unsigned int i) const
	{ return options[i]; }

	Option::Option(const std::string& name,
				   const std::string& short_name) :
			name(std::string(name)),
			short_name(std::string(short_name))
	{}

	void Program_options::add_option(const std::string& name,
									 const std::string& short_name)
	{
		std::string opt_name = std::string("--") + name;
		std::string opt_short_name = std::string("-") + short_name;
		options.emplace_back(opt_name, opt_short_name);
	}

	void Program_options::parse_command_line(int argc, char** argv)
	{
		enum state
		{
		};

		unsigned i = 1;
		while (i < argc && argv[i][0] != '-')
		{ ++i; }

		unsigned option_id;
		for (; i < argc; ++i)
		{
			if (argv[i][0] == '-')
			{
				option_id = option_index(argv[i]);
				if (option_id == options.size())
				{
					std::cout << "[options] Unknown option "
							  << argv[i]
							  << " ignored"
							  << std::endl;

					++i;
					while (i < argc && argv[i][0] != '-')
					{ ++i; }
					if (i == argc)
					{ return; }
					--i;
				}
				else
				{
					options[option_id].is_used = true;
					options[option_id].parameters.clear();
				}
			}
			else
			{
				options[option_id].parameters.emplace_back(argv[i]);
			}
		}
	}

	unsigned Program_options::option_index(const std::string& parsed_name)
	{
		unsigned i = 0;

		while (i < options.size())
		{
			if (options[i].name == parsed_name ||
				options[i].short_name == parsed_name)
			{
				return i;
			}
			++i;
		}
		return i;
	}
}