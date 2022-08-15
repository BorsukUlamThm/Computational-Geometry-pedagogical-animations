#pragma once

/** @cond */
#include <limits>
#include <string>
#include <map>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <boost/array.hpp>
/** @endcond */
#include "utils/File_management.h"


namespace graphics
{
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

	extern std::map<std::string, Color> names_to_colors;
	// std::map cannot be constexpr RIP :'(
	// will have to wait for someone to add it to the std or boost ...

	std::ostream& operator<<(std::ostream& os,
							 const Color& color);
	std::istream& operator>>(std::istream& is,
							 Color& color);

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
		explicit Config(const std::string& config_file = "dark_mode");

		/*!
		 * Returns the sfml color defined by the config
		 */
		sf::Color get_color(Color col) const;

	private:
		static sf::Color read_color(const std::vector<std::string>& words);
		void parse_config_line(const std::string& line,
							   const std::string& config_dir_path);
	};
}