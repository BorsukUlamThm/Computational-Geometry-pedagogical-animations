#pragma once

#include <SFML/System/String.hpp>
#include "Point_shp.h"
#include "Point_shp.h"


namespace graphics
{
	/*!
	 * A Text_shape is a text drawn on a Canvas\n
	 * It is designed to add some information about shapes. For example in order
	 * to add a label above a point\n
	 * It is defined by\n
	 *
	 * - A std::string with its content
	 * - The x y coordinate of the place in the plane where the text should be
	 * - The font size on the Canvas
	 * - An offset, in pixel to move the text on the Canvas
	 * - The text color
	 *
	 * For example, if you have a Point_shp point that you wish to label "Foo",
	 * you can use a Text_shp as with content "Foo", the same x y coordinate as
	 * point, and an a y offset large enough to place the text above the point
	 * on the canvas\n
	 * Actually you dont need to do this, you can use the constructor\n
	 * ```C
	 * Text_shp(const std::string& text,
	 *          const Point_shp& point,
	 *          unsigned size = 16,
	 *          const Color col = DEFAULT_SHAPE_COLOR)
	 * ```
	 * which was already designed for this use case, but it gives you an idea\n
	 */
	class Text_shp : public Shape
	{
	private:
		std::string content {};
		Point_obj point;
		unsigned size = 16;
		float offset_x = 0;
		float offset_y = 0;
		Color color = DEFAULT_SHAPE_COLOR;

	public:
		// standard constructors
		Text_shp();
		Text_shp(const std::string& text,
				 const Coordinate& x,
				 const Coordinate& y,
				 unsigned size = 16,
				 float off_x = 0,
				 float off_y = 0,
				 const Color col = DEFAULT_SHAPE_COLOR);
		Text_shp(const Text_shp& other);

		// other constructors
		/*!
		 * Constructs a text that will be drawn on the given point
		 */
		Text_shp(const std::string& text,
				 const Point_obj& point,
				 unsigned size = 16,
				 const Color col = DEFAULT_SHAPE_COLOR);
		/*!
		 * Constructs a text that will be drawn just above the given point
		 */
		Text_shp(const std::string& text,
				 const Point_shp& point,
				 unsigned size = 16,
				 const Color col = DEFAULT_SHAPE_COLOR);
		/*!
		 * Constructs a text that will be drawn in the middle of the given
		 * segment
		 */
		Text_shp(const std::string& text,
				 const Segment_obj& segment,
				 unsigned size = 16,
				 const Color col = DEFAULT_SHAPE_COLOR);

		~Text_shp() = default;

		std::string get_content() const;
		Coordinate get_abscissa() const;
		Coordinate get_ordinate() const;
		unsigned get_size() const;
		float get_offset_x() const;
		float get_offset_y() const;
		Color get_color() const;

		void draw(Canvas& canvas) const override;
		void write(std::ostream& os) const override;

	public:
		friend std::istream& operator>>(std::istream& is,
										Text_shp& text);
	};

	std::ostream& operator<<(std::ostream& os,
							 const Text_shp& text);
	std::istream& operator>>(std::istream& is,
							 Text_shp& text);
}