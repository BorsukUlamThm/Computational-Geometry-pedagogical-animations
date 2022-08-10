#pragma once

/** @cond */
#include <vector>
/** @endcond */
#include "Point_plot.h"


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
	class Polygon_plot : public Plot
	{
	private:
		std::vector<Point_plot> vertices;
		Color lines_color = DEFAULT_PLOT_COLOR;

	public:
		Polygon_plot() = default;
		explicit Polygon_plot(Color lines_col);
		explicit Polygon_plot(const std::vector<Point_plot>& vertices,
							  Color lines_col = DEFAULT_PLOT_COLOR);
		Polygon_plot(const Polygon_plot& other);

		void push_back(const Point_plot& vertex);
		void add_vertex(const Coordinate& x,
						const Coordinate& y);

		unsigned size() const;
		Point_plot& operator[](unsigned i);
		const Point_plot& operator[](unsigned i) const;
		Color get_lines_color() const;

		Coordinate get_min_abscissa() const override;
		Coordinate get_max_abscissa() const override;
		Coordinate get_min_ordinate() const override;
		Coordinate get_max_ordinate() const override;

		void draw(Canvas& canvas) const override;

		friend std::istream& operator>>(std::istream& is,
										Polygon_plot& polygon);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Polygon_plot::Polygon_plot(Color lines_col)
	{
		lines_color = lines_col;
	}

	Polygon_plot::Polygon_plot(const std::vector<Point_plot>& vertices,
							   Color lines_col)
	{
		this->vertices = std::vector<Point_plot>(vertices);
		lines_color = lines_col;
	}

	Polygon_plot::Polygon_plot(const Polygon_plot& other)
	{
		for(unsigned i = 0; i < other.size(); ++i)
		{
			vertices.emplace_back(other[i]);
		}
		lines_color = other.lines_color;
	}

	void Polygon_plot::push_back(const Point_plot& vertex)
	{
		vertices.emplace_back(vertex);
	}

	void Polygon_plot::add_vertex(const Coordinate& x,
								  const Coordinate& y)
	{
		vertices.emplace_back(x, y);
	}

	unsigned Polygon_plot::size() const
	{
		return vertices.size();
	}

	Point_plot& Polygon_plot::operator[](unsigned int i)
	{
		return vertices[i];
	}

	const Point_plot& Polygon_plot::operator[](unsigned int i) const
	{
		return vertices[i];
	}

	Color Polygon_plot::get_lines_color() const
	{
		return lines_color;
	}

	Coordinate Polygon_plot::get_min_abscissa() const
	{
		Coordinate res = vertices[0].get_min_abscissa();
		for(unsigned i = 1; i < size(); ++i)
		{
			res = std::min(res, vertices[i].get_min_abscissa());
		}
		return res;
	}

	Coordinate Polygon_plot::get_max_abscissa() const
	{
		Coordinate res = vertices[0].get_max_abscissa();
		for(unsigned i = 1; i < size(); ++i)
		{
			res = std::max(res, vertices[i].get_max_abscissa());
		}
		return res;
	}

	Coordinate Polygon_plot::get_min_ordinate() const
	{
		Coordinate res = vertices[0].get_min_ordinate();
		for(unsigned i = 1; i < size(); ++i)
		{
			res = std::min(res, vertices[i].get_min_ordinate());
		}
		return res;
	}

	Coordinate Polygon_plot::get_max_ordinate() const
	{
		Coordinate res = vertices[0].get_max_ordinate();
		for(unsigned i = 1; i < size(); ++i)
		{
			res = std::max(res, vertices[i].get_max_ordinate());
		}
		return res;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Polygon_plot& polygon)
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
							 Polygon_plot& polygon)
	{
		polygon.vertices.clear();
		unsigned nb_vertices;
		is >> nb_vertices;

		Point_plot tmp;
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