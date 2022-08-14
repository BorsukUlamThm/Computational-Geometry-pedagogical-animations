#pragma once

/** @cond */
#include <vector>
/** @endcond */
#include "Point_shp.h"


namespace graphics
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

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

	public:
		friend std::istream& operator>>(std::istream& is,
										Polygon_shp& polygon);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Polygon_shp::Polygon_shp(Color lines_col,
							 Color vertices_col)
	{
		lines_color = lines_col;
		vertices_color = vertices_col;
	}

	Polygon_shp::Polygon_shp(const Polygon_obj& vertices,
							 Color lines_col,
							 Color vertices_col)
	{
		this->vertices = Polygon_obj(vertices);
		lines_color = lines_col;
		vertices_color = vertices_col;
		bounding_box = Bounding_box(vertices);
	}

	Polygon_shp::Polygon_shp(const Polygon_shp& other) : Shape(other)
	{
		vertices = Polygon_obj(other.vertices);
		lines_color = other.lines_color;
		vertices_color = other.vertices_color;
	}

	void Polygon_shp::push_back(const Point_obj& vertex)
	{
		vertices.push_back(vertex);
	}

	void Polygon_shp::add_vertex(const Coordinate& x,
								 const Coordinate& y)
	{
		vertices.emplace_back(x, y);
		bounding_box.extend(x, y);
	}

	unsigned Polygon_shp::size() const
	{ return vertices.size(); }

	Point_obj& Polygon_shp::operator[](unsigned int i)
	{ return vertices[i]; }

	const Point_obj& Polygon_shp::operator[](unsigned int i) const
	{ return vertices[i]; }

	Color Polygon_shp::get_lines_color() const
	{ return lines_color; }

	Color Polygon_shp::get_vertices_color() const
	{ return vertices_color; }

	std::ostream& operator<<(std::ostream& os,
							 const Polygon_shp& polygon)
	{
		os << POLYGON_NAME << " "
		   << polygon.size() << " ";
		for (unsigned i = 0; i < polygon.size(); ++i)
		{
			os << polygon[i].abscissa << " "
			   << polygon[i].ordinate << " ";
		}

		os << polygon.get_lines_color() << " "
		   << polygon.get_vertices_color();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Polygon_shp& polygon)
	{
		polygon.vertices.clear();
		unsigned nb_vertices;
		is >> nb_vertices;

		Coordinate x, y;
		for (unsigned i = 0; i < nb_vertices; ++i)
		{
			is >> x >> y;
			polygon.add_vertex(x, y);
		}

		is >> polygon.lines_color
		   >> polygon.vertices_color;
		return is;
	}
}