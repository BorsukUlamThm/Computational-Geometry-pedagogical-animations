#include "graphics/model/global_variables.h"
#include "utils/file_management.h"


namespace graphics
{
	std::map<std::string, Color> names_to_colors
			{
					{"BLACK",               BLACK},
					{"WHITE",               WHITE},
					{"RED",                 RED},
					{"PURPLE",              PURPLE},
					{"BLUE",                BLUE},
					{"GREEN",               GREEN},
					{"YELLOW",              YELLOW},
					{"BACKGROUND_COLOR",    BACKGROUND_COLOR},
					{"DEFAULT_SHAPE_COLOR", DEFAULT_SHAPE_COLOR}
			};

	std::ostream& operator<<(std::ostream& os,
							 const Color& color)
	{
		os << colors_to_names[color];
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Color& color)
	{
		std::string tmp;
		is >> tmp;
		color = names_to_colors[tmp];
		return is;
	}

	Config::Config(const std::string& config_file)
	{
		colors[BLACK] = sf::Color(33, 47, 60);
		colors[WHITE] = sf::Color(208, 211, 212);
		colors[RED] = sf::Color(203, 67, 53);
		colors[PURPLE] = sf::Color(175, 122, 197);
		colors[BLUE] = sf::Color(52, 152, 219);
		colors[GREEN] = sf::Color(39, 174, 96);
		colors[YELLOW] = sf::Color(241, 196, 15);
		colors[BACKGROUND_COLOR] = colors[BLACK];
		colors[DEFAULT_SHAPE_COLOR] = colors[WHITE];

		std::filesystem::path config_dir = utils::get_config_directory();
		if (config_dir.empty())
		{ return; }

		std::ifstream ifs(config_dir.string() + "/" + config_file);
		std::string line;

		for (; !ifs.eof(); std::getline(ifs, line))
		{
			parse_config_line(line, config_dir.string());
		}
		parse_config_line(line, config_dir.string());
	}

	sf::Color Config::get_color(Color col) const
	{
		if (col < NB_COLORS)
		{ return colors[col]; }

		return sf::Color(0, 0, 0);
	}

	sf::Color Config::read_color(const std::vector<std::string>& words)
	{
		unsigned r = std::stoi(words[1]);
		unsigned g = std::stoi(words[2]);
		unsigned b = std::stoi(words[3]);
		return sf::Color(r, g, b);
	}

	void Config::parse_config_line(const std::string& line,
								   const std::string& config_dir_path)
	{
		if (line.empty())
		{ return; }

		std::vector<std::string> words = utils::split_line(line);
		if (words[0][0] == '#')
		{ return; }

		if (words[0] == "BLACK")
		{ colors[BLACK] = read_color(words); }
		else if (words[0] == "WHITE")
		{ colors[WHITE] = read_color(words); }
		else if (words[0] == "RED")
		{ colors[RED] = read_color(words); }
		else if (words[0] == "PURPLE")
		{ colors[PURPLE] = read_color(words); }
		else if (words[0] == "BLUE")
		{ colors[BLUE] = read_color(words); }
		else if (words[0] == "GREEN")
		{ colors[GREEN] = read_color(words); }
		else if (words[0] == "YELLOW")
		{ colors[YELLOW] = read_color(words); }
		else if (words[0] == "BACKGROUND_COLOR")
		{ colors[BACKGROUND_COLOR] = read_color(words); }
		else if (words[0] == "PLOT_COLOR")
		{ colors[DEFAULT_SHAPE_COLOR] = read_color(words); }

		if (words[0] == "FONT")
		{
			std::string font_file = config_dir_path
									+ "/Fonts/" + words[1] + ".ttf";
			if (!font.loadFromFile(font_file))
			{
				std::cout << "No font found at "
						  << font_file
						  << std::endl;
			}
		}

		if (words[0] == "WIDTH")
		{ width = std::stoi(words[1]); }
		if (words[0] == "HEIGHT")
		{ height = std::stoi(words[1]); }
		if (words[0] == "MARGIN")
		{ margin = std::stoi(words[1]); }
	}
}