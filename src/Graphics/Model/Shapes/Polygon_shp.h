#pragma once

/** @cond */
#include <vector>
/** @endcond */
#include "Point_shp.h"


namespace gr
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * Contains the needed information to draw a circle\n
	 * \n
	 * -> list of the vertices\n
	 * -> color\n
	 */
	class Polygon_shp : public Shape
	{
	private:
		std::vector<Point_shp> vertices;
		Color lines_color = DEFAULT_PLOT_COLOR;

	public:
		Polygon_shp() = default;
		explicit Polygon_shp(Color lines_col);
		explicit Polygon_shp(const std::vector<Point_shp>& vertices,
							 Color lines_col = DEFAULT_PLOT_COLOR);
		Polygon_shp(const Polygon_shp& other);

		void push_back(const Point_shp& vertex);
		void add_vertex(const Coordinate& x,
						const Coordinate& y);

		unsigned size() const;
		Point_shp& operator[](unsigned i);
		const Point_shp& operator[](unsigned i) const;
		Color get_lines_color() const;

		Coordinate get_min_abscissa() const override;
		Coordinate get_max_abscissa() const override;
		Coordinate get_min_ordinate() const override;
		Coordinate get_max_ordinate() const override;

		void draw(Canvas& canvas) const override;

		friend std::istream& operator>>(std::istream& is,
										Polygon_shp& polygon);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Polygon_shp::Polygon_shp(Color lines_col)
	{
		lines_color = lines_col;
	}

	Polygon_shp::Polygon_shp(const std::vector<Point_shp>& vertices,
							 Color lines_col)
	{
		this->vertices = std::vector<Point_shp>(vertices);
		lines_color = lines_col;
	}

	Polygon_shp::Polygon_shp(const Polygon_shp& other)
	{
		for(unsigned i = 0; i < other.size(); ++i)
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
	{
		return vertices.size();
	}

	Point_shp& Polygon_shp::operator[](unsigned int i)
	{
		return vertices[i];
	}

	const Point_shp& Polygon_shp::operator[](unsigned int i) const
	{
		return vertices[i];
	}

	Color Polygon_shp::get_lines_color() const
	{
		return lines_color;
	}

	Coordinate Polygon_shp::get_min_abscissa() const
	{
		Coordinate res = vertices[0].get_min_abscissa();
		for(unsigned i = 1; i < size(); ++i)
		{
			res = std::min(res, vertices[i].get_min_abscissa());
		}
		return res;
	}

	Coordinate Polygon_shp::get_max_abscissa() const
	{
		Coordinate res = vertices[0].get_max_abscissa();
		for(unsigned i = 1; i < size(); ++i)
		{
			res = std::max(res, vertices[i].get_max_abscissa());
		}
		return res;
	}

	Coordinate Polygon_shp::get_min_ordinate() const
	{
		Coordinate res = vertices[0].get_min_ordinate();
		for(unsigned i = 1; i < size(); ++i)
		{
			res = std::min(res, vertices[i].get_min_ordinate());
		}
		return res;
	}

	Coordinate Polygon_shp::get_max_ordinate() const
	{
		Coordinate res = vertices[0].get_max_ordinate();
		for(unsigned i = 1; i < size(); ++i)
		{
			res = std::max(res, vertices[i].get_max_ordinate());
		}
		return res;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Polygon_shp& polygon)
	{
		os << POLYGON_NAME << " "
		   << polygon.size() << " ";
		for(unsigned i = 0; i < polygon.size(); ++i)
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

		for(unsigned i = 0; i < nb_vertices; ++i)
		{
			is >> dummy;
			is >> tmp;
			polygon.push_back(tmp);
		}
		return is;
	}
}