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
		std::vector<Point_shp> vertices;
		Color lines_color = DEFAULT_SHAPE_COLOR;

	public:
		Polygon_shp();
		explicit Polygon_shp(Color lines_col);
		explicit Polygon_shp(const std::vector<Point_shp>& vertices,
							 Color lines_col = DEFAULT_SHAPE_COLOR);
		Polygon_shp(const Polygon_shp& other);

		void push_back(const Point_shp& vertex);
		void add_vertex(const Coordinate& x,
						const Coordinate& y);

		unsigned size() const;
		Point_shp& operator[](unsigned i);
		const Point_shp& operator[](unsigned i) const;
		Color get_lines_color() const;

		void draw(Canvas& canvas) const override;

	private:
		void make_bounding_box();

	public:
		friend std::istream& operator>>(std::istream& is,
										Polygon_shp& polygon);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Polygon_shp::Polygon_shp()
	{
		make_bounding_box();
	}

	Polygon_shp::Polygon_shp(Color lines_col)
	{
		lines_color = lines_col;
		make_bounding_box();
	}

	Polygon_shp::Polygon_shp(const std::vector<Point_shp>& vertices,
							 Color lines_col)
	{
		this->vertices = std::vector<Point_shp>(vertices);
		lines_color = lines_col;
		make_bounding_box();
	}

	Polygon_shp::Polygon_shp(const Polygon_shp& other) : Shape(other)
	{
		for (unsigned i = 0; i < other.size(); ++i)
		{
			vertices.emplace_back(other[i]);
		}
		lines_color = other.lines_color;
	}

	void Polygon_shp::push_back(const Point_shp& vertex)
	{
		vertices.emplace_back(vertex);
	}

	void Polygon_shp::add_vertex(const Coordinate& x,
								 const Coordinate& y)
	{
		vertices.emplace_back(x, y);
	}

	unsigned Polygon_shp::size() const
	{ return vertices.size(); }

	Point_shp& Polygon_shp::operator[](unsigned int i)
	{ return vertices[i]; }

	const Point_shp& Polygon_shp::operator[](unsigned int i) const
	{ return vertices[i]; }

	Color Polygon_shp::get_lines_color() const
	{ return lines_color; }

	void Polygon_shp::make_bounding_box()
	{
		bounding_box.clear();
		for (auto& vertex : vertices)
		{
			bounding_box.extend(vertex.get_bounding_box());
		}
	}

	std::ostream& operator<<(std::ostream& os,
							 const Polygon_shp& polygon)
	{
		os << POLYGON_NAME << " "
		   << polygon.size() << " ";
		for (unsigned i = 0; i < polygon.size(); ++i)
		{
			os << polygon[i] << " ";
		}
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Polygon_shp& polygon)
	{
		polygon.vertices.clear();
		unsigned nb_vertices;
		is >> nb_vertices;

		Point_shp tmp;
		std::string dummy;

		for (unsigned i = 0; i < nb_vertices; ++i)
		{
			is >> dummy;
			is >> tmp;
			polygon.push_back(tmp);
		}
		return is;
	}
}