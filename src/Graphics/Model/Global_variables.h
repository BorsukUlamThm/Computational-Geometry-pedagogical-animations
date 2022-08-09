#pragma once

/** @cond */
#include <limits>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
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
		DEFAULT_BACKGROUND_COLOR,
		DEFAULT_PLOT_COLOR
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
		sf::Color dark_grey = sf::Color(33, 47, 60);
		sf::Color light_grey = sf::Color(208, 211, 212);

		sf::Color red = sf::Color(203, 67, 53);
		sf::Color purple = sf::Color(175, 122, 197);
		sf::Color blue = sf::Color(52, 152, 219);
		sf::Color green = sf::Color(39, 174, 96);
		sf::Color yellow = sf::Color(241, 196, 15);

		sf::Color default_background_color = dark_grey;
		sf::Color default_plot_color = light_grey;

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
				{ dark_grey = read_color(words); }
				if(words[0] == "LIGHT_GREY")
				{ light_grey = read_color(words); }
				if(words[0] == "RED")
				{ red = read_color(words); }
				if(words[0] == "PURPLE")
				{ purple = read_color(words); }
				if(words[0] == "BLUE")
				{ blue = read_color(words); }
				if(words[0] == "GREEN")
				{ green = read_color(words); }
				if(words[0] == "YELLOW")
				{ yellow = read_color(words); }
				if(words[0] == "BACKGROUND_COLOR")
				{ default_background_color = read_color(words); }
				if(words[0] == "PLOT_COLOR")
				{ default_plot_color = read_color(words); }

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
			switch(col)
			{
				case DARK_GREY:
					return dark_grey;
				case LIGHT_GREY:
					return light_grey;
				case RED:
					return red;
				case PURPLE:
					return purple;
				case BLUE:
					return blue;
				case GREEN:
					return green;
				case YELLOW:
					return yellow;
				case DEFAULT_BACKGROUND_COLOR:
					return default_background_color;
				case DEFAULT_PLOT_COLOR:
					return default_plot_color;
			}

			return sf::Color(0, 0, 0);
		}
	};
}