#pragma once

#include "Shape.h"


namespace graphics
{
	/*!
	 * A Circle_shp is a circle drawn on a Canvas\n
	 * It is defined by\n
	 *
	 * - The x y coordinates of the center of the represented circle
	 * - The radius of the represented circle
	 * - The color of the circle on the Canvas
	 *
	 * Note that the x y coordinate are the cartesian coordinate of the abstract
	 * circle center, not its position on the Canvas in pixel\n
	 * In the same way, the radius it the radius of the abstract circle, and not
	 * the radius of the circle drawn on the canvas\n
	 */
	class Circle_shp : public Shape
	{
	private:
		Circle_obj circle;
		Color color = DEFAULT_SHAPE_COLOR;

	public:
		Circle_shp();
		Circle_shp(const Coordinate& x,
				   const Coordinate& y,
				   const Coordinate& rad,
				   Color col = DEFAULT_SHAPE_COLOR);
		Circle_shp(const Circle_shp& other);

		~Circle_shp() = default;

		Coordinate get_center_x() const;
		Coordinate get_center_y() const;
		Coordinate get_radius() const;
		Color get_color() const;

		void draw(Canvas& canvas) const override;
		void write(std::ostream& os) const override;

	public:
		friend std::istream& operator>>(std::istream& is,
										Circle_shp& circle);
	};

	std::ostream& operator<<(std::ostream& os,
							 const Circle_shp& circle);
	std::istream& operator>>(std::istream& is,
							 Circle_shp& circle);
}