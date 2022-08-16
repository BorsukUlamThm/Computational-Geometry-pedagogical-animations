#pragma once

#include "Shape.h"


namespace graphics
{
	/*!
	 * A Polygon_shp is a polygon drawn on a Canvas\n
	 * It is defined by\n
	 *
	 * - A vector of Point_shp that represents its vertices\n
	 * - The color of the line between them on the Canvas\n
	 */
	class Polygon_shp : public Shape
	{
	private:
		Polygon_obj vertices;
		Color lines_color = DEFAULT_SHAPE_COLOR;
		Color vertices_color = DEFAULT_SHAPE_COLOR;

	public:
		explicit Polygon_shp(Color lines_col = DEFAULT_SHAPE_COLOR,
							 Color vertices_col = DEFAULT_SHAPE_COLOR);
		explicit Polygon_shp(const Polygon_obj& vertices,
							 Color lines_col = DEFAULT_SHAPE_COLOR,
							 Color vertices_col = DEFAULT_SHAPE_COLOR);
		Polygon_shp(const Polygon_shp& other);

		void push_back(const Point_obj& vertex);
		void add_vertex(const Coordinate& x,
						const Coordinate& y);

		unsigned size() const;
		Point_obj& operator[](unsigned i);
		const Point_obj& operator[](unsigned i) const;
		Color get_lines_color() const;
		Color get_vertices_color() const;

		void draw(Canvas& canvas) const override;
		void write(std::ostream& os) const override;

	public:
		friend std::istream& operator>>(std::istream& is,
										Polygon_shp& polygon);
	};

	std::ostream& operator<<(std::ostream& os,
							 const Polygon_shp& polygon);
	std::istream& operator>>(std::istream& is,
							 Polygon_shp& polygon);
}