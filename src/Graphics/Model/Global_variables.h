#pragma once

/** @cond */
#include <limits>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <boost/array.hpp>
/** @endcond */
#include "General_tools/General_tools.h"


namespace gr
{
	// Some types for the objects coordinates
	typedef float Coordinate;

	typedef std::numeric_limits<Coordinate> limits;
	constexpr Coordinate MIN_COORDINATE = limits::lowest();
	constexpr Coordinate MAX_COORDINATE = limits::max();


	// Class names for serialization
	constexpr char POINT_NAME[] = "Point";
	constexpr char SEGMENT_NAME[] = "Segment";
	constexpr char VECTOR_NAME[] = "Vector";
	constexpr char POLYGON_NAME[] = "Polygon";
	constexpr char CIRCLE_NAME[] = "Circle";
	constexpr char LINE_NAME[] = "Line";
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
		DEFAULT_PLOT_COLOR,
		NB_COLORS
	};

	/*!
	 * Contains all the needed information to draw shapes\n
	 * \n
	 * -> r g b values of each color\n
	 * -> default background color\n
	 * -> default plot color\n
	 * -> font used for writings\n
	 * -> size of the window and a margin\n
	 */
	struct Config
	{
		std::string window_title = "CGPA";

		boost::array<sf::Color, NB_COLORS> colors;

		sf::Font font;

		unsigned width = 1600;
		unsigned height = 900;
		unsigned margin = 20;

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
			colors[DEFAULT_PLOT_COLOR] = colors[LIGHT_GREY];

			std::filesystem::path config_dir = gt::get_config_directory();
			if(config_dir.empty())
			{ return; }

			std::ifstream is (config_dir.string() + "/config");
			std::string line;

			for(;!is.eof(); std::getline(is, line))
			{
				if(line.empty())
				{ continue; }

				std::vector<std::string> words = gt::split_line(line);
				if(words[0][0] == '#')
				{ continue; }

				if(words[0] == "DARK_GREY")
				{ colors[DARK_GREY] = read_color(words); }
				if(words[0] == "LIGHT_GREY")
				{ colors[LIGHT_GREY] = read_color(words); }
				if(words[0] == "RED")
				{ colors[RED] = read_color(words); }
				if(words[0] == "PURPLE")
				{ colors[PURPLE] = read_color(words); }
				if(words[0] == "BLUE")
				{ colors[BLUE] = read_color(words); }
				if(words[0] == "GREEN")
				{ colors[GREEN] = read_color(words); }
				if(words[0] == "YELLOW")
				{ colors[YELLOW] = read_color(words); }
				if(words[0] == "BACKGROUND_COLOR")
				{ colors[BACKGROUND_COLOR] = read_color(words); }
				if(words[0] == "PLOT_COLOR")
				{ colors[DEFAULT_PLOT_COLOR] = read_color(words); }

				if(words[0] == "FONT")
				{
					std::string font_file = config_dir.string()
											+ "/Fonts/" + words[1] + ".ttf";
					if(!font.loadFromFile(font_file))
					{
						std::cout << "No font found at "
								  << font_file
								  << std::endl;
					}
				}

				if(words[0] == "WIDTH")
				{ width = std::stoi(words[1]); }
				if(words[0] == "HEIGHT")
				{ height = std::stoi(words[1]); }
				if(words[0] == "MARGIN")
				{ margin = std::stoi(words[1]); }
			}
		}

		/*!
		 * @param words the words parsed from a line in a config file
		 * @return the color defined from the r g b values
		 */
		static sf::Color read_color(const std::vector<std::string>& words)
		{
			unsigned r = std::stoi(words[1]);
			unsigned g = std::stoi(words[2]);
			unsigned b = std::stoi(words[3]);
			return sf::Color(r, g, b);
		}

		/*!
		 * @param col an available colour
		 * @return the SFML colour defined by the Config
		 */
		sf::Color get_color(Color col) const
		{
			if (col < NB_COLORS)
			{
				return colors[col];
			}

			return sf::Color(0, 0, 0);
		}
	};
}