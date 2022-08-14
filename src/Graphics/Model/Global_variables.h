#pragma once

/** @cond */
#include <limits>
#include <string>
#include <map>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <boost/array.hpp>
/** @endcond */
#include "General_tools/General_tools.h"


namespace graphics
{
	namespace gt = general_tools;

	// Some types for the objects coordinates
	typedef float Coordinate;

	typedef std::numeric_limits<Coordinate> limits;
	constexpr Coordinate MIN_COORDINATE = limits::lowest();
	constexpr Coordinate MAX_COORDINATE = limits::max();


	// Shapes names for serialization
	constexpr char POINT_NAME[] = "[Point]";
	constexpr char SEGMENT_NAME[] = "[Segment]";
	constexpr char LINE_NAME[] = "[Line]";
	constexpr char CIRCLE_NAME[] = "[Circle]";
	constexpr char POLYGON_NAME[] = "[Polygon]";
	constexpr char VECTOR_NAME[] = "[Vector]";
	constexpr char TEXT_NAME[] = "[Text]";

	/*!
	 * Available colours
	 */
	enum Color
	{
		BLACK,
		WHITE,
		RED,
		PURPLE,
		BLUE,
		GREEN,
		YELLOW,
		BACKGROUND_COLOR,
		DEFAULT_SHAPE_COLOR,
		NB_COLORS
	};

	constexpr boost::array<const char*, NB_COLORS> colors_to_names
			{
					(const char*) "BLACK",
					(const char*) "WHITE",
					(const char*) "RED",
					(const char*) "PURPLE",
					(const char*) "BLUE",
					(const char*) "GREEN",
					(const char*) "YELLOW",
					(const char*) "BACKGROUND_COLOR",
					(const char*) "DEFAULT_SHAPE_COLOR"
			};

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
	// std::map cannot be constexpr RIP :'(
	// will have to wait for someone to add it to the std or boost ...

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

	/*!
	 * The Config class contains all the needed information to draw shapes\n
	 *
	 * - r g b values of each color
	 * - background color
	 * - default plot color
	 * - font used for writings
	 * - size of the window and margin
	 */
	struct Config
	{
		boost::array<sf::Color, NB_COLORS> colors;
		sf::Font font;

		unsigned width = -1;
		unsigned height = -1;
		unsigned margin = 50;

		/*!
		 * Constructs a Config object reading the values from the config_file\n
		 * If the config_file is not found, default values are set instead
		 */
		explicit Config(const std::string& config_file = "dark_mode.cfg")
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

			std::filesystem::path config_dir = gt::get_config_directory();
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

		static sf::Color read_color(const std::vector<std::string>& words)
		{
			unsigned r = std::stoi(words[1]);
			unsigned g = std::stoi(words[2]);
			unsigned b = std::stoi(words[3]);
			return sf::Color(r, g, b);
		}

		void parse_config_line(const std::string& line,
							   const std::string& config_dir_path)
		{
			if (line.empty())
			{ return; }

			std::vector<std::string> words = gt::split_line(line);
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

		sf::Color get_color(Color col) const
		{
			if (col < NB_COLORS)
			{ return colors[col]; }

			return sf::Color(0, 0, 0);
		}
	};
}