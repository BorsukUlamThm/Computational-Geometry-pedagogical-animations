#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Shape.h"


namespace graphics
{
	/*!
	 * A Point_shp is a point drawn on a Canvas\n
	 * It is defined by\n
	 *
	 * - The x y coordinates of the represented point
	 * - The color of the point on the Canvas
	 * - The radius of the point on the Canvas, in pixel
	 *
	 * Note that the x y coordinate are the cartesian coordinate of the abstract
	 * point, not its position on the Canvas in pixel\n
	 */
	class Point_shp : public Shape
	{
	private:
		Point_obj point;
		Color color = DEFAULT_SHAPE_COLOR;
		float radius = 3;

	public:
		Point_shp();
		Point_shp(const Coordinate& x,
				  const Coordinate& y,
				  Color col = DEFAULT_SHAPE_COLOR,
				  float rad = 3);
		Point_shp(const Point_shp& other);

		~Point_shp() = default;

		Coordinate get_abscissa() const;
		Coordinate get_ordinate() const;
		Color get_color() const;
		float get_radius() const;

		void draw(Canvas& canvas) const override;
		void write(std::ostream& os) const override;

	public:
		friend std::istream& operator>>(std::istream& is,
										Point_shp& point);
	};

	std::ostream& operator<<(std::ostream& os,
							 const Point_shp& point);
	std::istream& operator>>(std::istream& is,
							 Point_shp& point);
}