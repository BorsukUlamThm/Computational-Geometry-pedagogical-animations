#pragma once

/** @cond */
#include <limits>
#include <string>
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


	// Class names for serialization
	constexpr char POINT_NAME[] = "Point";
	constexpr char SEGMENT_NAME[] = "Segment";
	constexpr char LINE_NAME[] = "Line";
	constexpr char CIRCLE_NAME[] = "Circle";
	constexpr char POLYGON_NAME[] = "Polygon";
	constexpr char VECTOR_NAME[] = "Vector";
	constexpr char TEXT_NAME[] = "Text";

	/*!
	 * Available colours
	 */
	enum Color
	{
		DARK_GREY,
		LIGHT_GREY,
		RED,
		PURPLE,
		BLUE,
		GREEN,
		YELLOW,
		BACKGROUND_COLOR,
		DEFAULT_SHAPE_COLOR,
		NB_COLORS
	};

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
		std::string window_title = "CGPA";

		boost::array<sf::Color, NB_COLORS> colors;

		sf::Font font;

		unsigned width = -1;
		unsigned height = -1;
		unsigned margin = 50;

		/*!
		 * Constructs a Config object reading the values from the config file \n
		 * If the config file is not found, default values are set instead
		 */
		Config()
		{
			colors[DARK_GREY] = sf::Color(33, 47, 60);
			colors[LIGHT_GREY] = sf::Color(208, 211, 212);
			colors[RED] = sf::Color(203, 67, 53);
			colors[PURPLE] = sf::Color(175, 122, 197);
			colors[BLUE] = sf::Color(52, 152, 219);
			colors[GREEN] = sf::Color(39, 174, 96);
			colors[YELLOW] = sf::Color(241, 196, 15);
			colors[BACKGROUND_COLOR] = colors[DARK_GREY];
			colors[DEFAULT_SHAPE_COLOR] = colors[LIGHT_GREY];

			std::filesystem::path config_dir = gt::get_config_directory();
			if (config_dir.empty())
			{ return; }

			std::ifstream is(config_dir.string() + "/config");
			std::string line;

			for (; !is.eof(); std::getline(is, line))
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

			if (words[0] == "DARK_GREY")
			{ colors[DARK_GREY] = read_color(words); }
			if (words[0] == "LIGHT_GREY")
			{ colors[LIGHT_GREY] = read_color(words); }
			if (words[0] == "RED")
			{ colors[RED] = read_color(words); }
			if (words[0] == "PURPLE")
			{ colors[PURPLE] = read_color(words); }
			if (words[0] == "BLUE")
			{ colors[BLUE] = read_color(words); }
			if (words[0] == "GREEN")
			{ colors[GREEN] = read_color(words); }
			if (words[0] == "YELLOW")
			{ colors[YELLOW] = read_color(words); }
			if (words[0] == "BACKGROUND_COLOR")
			{ colors[BACKGROUND_COLOR] = read_color(words); }
			if (words[0] == "PLOT_COLOR")
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