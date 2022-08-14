#pragma once

/** @cond */
#include <memory>
/** @endcond */

#include "Shapes/Polygon_shp.h"
#include "Shapes/Circle_shp.h"
#include "Shapes/Line_shp.h"
#include "Shapes/Text_shp.h"


namespace graphics
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	typedef std::shared_ptr<Shape> Shape_ptr;

	/*!
	 * A Figure is a set of Shape that will be drawn on a Canvas\n
	 * The shapes are drawn in the same order they were added\n
	 * All the add_X methods add an X shape calling the appropriate constructor
	 */
	class Figure
	{
	private:
		std::vector<Shape_ptr> shapes;
		Bounding_box bounding_box {};
		bool need_remake_bounding_box = false;

	public:
		Figure() = default;
		/*!
		 * Constructs a figures with the shapes of all the given figures
		 */
		template<typename... Figures>
		explicit Figure(const Figure& figure,
						const Figures& ... figures);

		~Figure() = default;

		Bounding_box get_bounding_box() const;
		Coordinate get_min_abscissa() const;
		Coordinate get_max_abscissa() const;
		Coordinate get_min_ordinate() const;
		Coordinate get_max_ordinate() const;
		Shape_ptr get_last_shape() const;

		void add_point(const Point_shp& point);
		void add_point(const Coordinate& x,
					   const Coordinate& y,
					   Color col = DEFAULT_SHAPE_COLOR,
					   float rad = 3);
		template<typename... Points>
		void add_point(const Point_shp& point,
					   const Points& ... points);

		void add_segment(const Segment_shp& segment);
		void add_segment(const Coordinate& ogn_x,
						 const Coordinate& ogn_y,
						 const Coordinate& dst_x,
						 const Coordinate& dst_y,
						 Color line_col = DEFAULT_SHAPE_COLOR,
						 Color end_points_col = DEFAULT_SHAPE_COLOR);
		template<typename... Segments>
		void add_segment(const Segment_shp& segment,
						 const Segments& ... segments);

		void add_vector(const Vector_shp& vector);
		void add_vector(const Coordinate& ogn_x,
						const Coordinate& ogn_y,
						const Coordinate& dst_x,
						const Coordinate& dst_y,
						Color col = DEFAULT_SHAPE_COLOR);
		void add_vector(const Point_obj& ogn,
						const Point_obj& dst,
						Color col = DEFAULT_SHAPE_COLOR);
		void add_vector(const Segment_obj& segment,
						Color col = DEFAULT_SHAPE_COLOR);
		template<typename... Vectors>
		void add_vector(const Vector_shp& vector,
						const Vectors& ... vectors);

		void add_polygon(const Polygon_shp& polygon);
		void add_polygon(const Polygon_obj& vertices,
						 Color lines_col = DEFAULT_SHAPE_COLOR,
						 Color vertices_col = DEFAULT_SHAPE_COLOR);
		template<typename... Polygons>
		void add_polygon(const Polygon_shp& polygon,
						 const Polygons& ... polygons);

		void add_circle(const Circle_shp& circle);
		void add_circle(const Coordinate& x,
						const Coordinate& y,
						const Coordinate& rad,
						Color col = DEFAULT_SHAPE_COLOR);
		template<typename... Circles>
		void add_circle(const Circle_shp& circle,
						const Circles& ... circles);

		void add_line(const Line_shp& line);
		void add_line(const Coordinate& a,
					  const Coordinate& b,
					  const Coordinate& c,
					  Color col = DEFAULT_SHAPE_COLOR);
		void add_line(const Segment_obj& segment,
					  Color col = DEFAULT_SHAPE_COLOR);
		void add_line(const Point_obj& point1,
					  const Point_obj& point2,
					  Color col = DEFAULT_SHAPE_COLOR);
		void add_line(const Coordinate& x1,
					  const Coordinate& y1,
					  const Coordinate& x2,
					  const Coordinate& y2,
					  Color col = DEFAULT_SHAPE_COLOR);
		template<typename... Lines>
		void add_line(const Line_shp& line,
					  const Lines& ... lines);

		void add_vertical_line(const Coordinate& x,
							   Color col = DEFAULT_SHAPE_COLOR);
		void add_horizontal_line(const Coordinate& y,
								 Color col = DEFAULT_SHAPE_COLOR);

		void add_text(const Text_shp& text);
		void add_text(const std::string& text,
					  const Coordinate& x,
					  const Coordinate& y,
					  unsigned size = 16,
					  float off_x = 0,
					  float off_y = 0,
					  Color col = DEFAULT_SHAPE_COLOR);
		void add_text(const std::string& text,
					  const Point_shp& point,
					  unsigned size = 16,
					  Color col = DEFAULT_SHAPE_COLOR);
		void add_text(const std::string& text,
					  const Segment_shp& segment,
					  unsigned size = 16,
					  Color col = DEFAULT_SHAPE_COLOR);
		void add_text(const std::string& text,
					  const Vector_shp& vector,
					  unsigned size = 16,
					  Color col = DEFAULT_SHAPE_COLOR);

		/*!
		 * Adds all the shapes of the other Figure
		 */
		void merge_figure(const Figure& other);
		template<typename... Figures>
		void merge_figure(const Figure& figure,
						  const Figures& ... figures);

		/*!
		 * Erases the last added Shape \n
		 * This can affect the Bounding_box,
		 * make_bounding_box() should be called before adding a new Shape
		 */
		void erase_last_shape();
		/*!
		 * Erases the last k added shape \n
		 * This can affect the Bounding_box,
		 * make_bounding_box() should be called before adding a new Shape
		 */
		void erase_last_k_shapes(unsigned k);
		/*!
		 * Updates the Bounding_box if needed\n
		 * This should be called after erasing some shapes
		 */
		void make_bounding_box();
		void clear();

		unsigned nb_shapes() const;
		bool is_empty() const;
		const Shape_ptr& operator[](unsigned i) const;
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	template<typename... Figures>
	Figure::Figure(const Figure& figure,
				   const Figures& ... figures)
	{
		merge_figure(figure);
		merge_figure(figures...);
	}

	Bounding_box Figure::get_bounding_box() const
	{ return bounding_box; }

	Coordinate Figure::get_min_abscissa() const
	{ return bounding_box.get_min_abscissa(); }

	Coordinate Figure::get_max_abscissa() const
	{ return bounding_box.get_max_abscissa(); }

	Coordinate Figure::get_min_ordinate() const
	{ return bounding_box.get_min_ordinate(); }

	Coordinate Figure::get_max_ordinate() const
	{ return bounding_box.get_max_ordinate(); }

	Shape_ptr Figure::get_last_shape() const
	{ return shapes.back(); }

	void Figure::add_point(const Point_shp& point)
	{
		Shape_ptr shape = std::make_shared<Point_shp>(point);
		shapes.push_back(shape);
		bounding_box.extend(point.get_bounding_box());
	}

	void Figure::add_point(const Coordinate& x,
						   const Coordinate& y,
						   Color col,
						   float rad)
	{
		Point_shp point(x, y, col, rad);
		add_point(point);
	}

	template<typename... Points>
	void Figure::add_point(const Point_shp& point,
						   const Points& ... points)
	{
		add_point(point);
		add_point(points...);
	}

	void Figure::add_segment(const Segment_shp& segment)
	{
		Shape_ptr shape = std::make_shared<Segment_shp>(segment);
		shapes.push_back(shape);
		bounding_box.extend(segment.get_bounding_box());
	}

	void Figure::add_segment(const Coordinate& ogn_x,
							 const Coordinate& ogn_y,
							 const Coordinate& dst_x,
							 const Coordinate& dst_y,
							 Color line_col,
							 Color end_points_col)
	{
		Segment_shp segment(ogn_x, ogn_y, dst_x, dst_y,
							line_col, end_points_col);
		add_segment(segment);
	}

	template<typename... Segments>
	void Figure::add_segment(const Segment_shp& segment,
							 const Segments& ... segments)
	{
		add_segment(segment);
		add_segment(segments...);
	}

	void Figure::add_vector(const Vector_shp& vector)
	{
		Shape_ptr shape = std::make_shared<Vector_shp>(vector);
		shapes.push_back(shape);
		bounding_box.extend(vector.get_bounding_box());
	}

	void Figure::add_vector(const Coordinate& ogn_x,
							const Coordinate& ogn_y,
							const Coordinate& dst_x,
							const Coordinate& dst_y,
							Color col)
	{
		Vector_shp vector(ogn_x, ogn_y, dst_x, dst_y, col);
		add_vector(vector);
	}

	void Figure::add_vector(const Point_obj& ogn,
							const Point_obj& dst,
							Color col)
	{
		Vector_shp vector(ogn, dst, col);
		add_vector(vector);
	}

	void Figure::add_vector(const Segment_obj& segment,
							Color col)
	{
		Vector_shp vector(segment, col);
		add_vector(vector);
	}

	template<typename... Vectors>
	void Figure::add_vector(const Vector_shp& vector,
							const Vectors& ... vectors)
	{
		add_vector(vector);
		add_vector(vectors...);
	}

	void Figure::add_polygon(const Polygon_shp& polygon)
	{
		Shape_ptr shape = std::make_shared<Polygon_shp>(polygon);
		shapes.push_back(shape);
		bounding_box.extend(polygon.get_bounding_box());
	}

	void Figure::add_polygon(const Polygon_obj& vertices,
							 Color lines_col,
							 Color vertices_col)
	{
		Polygon_shp polygon(vertices, lines_col, vertices_col);
		add_polygon(polygon);
	}

	template<typename... Polygons>
	void Figure::add_polygon(const Polygon_shp& polygon,
							 const Polygons& ... polygons)
	{
		add_polygon(polygon);
		add_polygon(polygons...);
	}

	void Figure::add_circle(const Circle_shp& circle)
	{
		Shape_ptr shape = std::make_shared<Circle_shp>(circle);
		shapes.push_back(shape);
		bounding_box.extend(circle.get_bounding_box());
	}

	void Figure::add_circle(const Coordinate& x,
							const Coordinate& y,
							const Coordinate& rad,
							Color col)
	{
		Circle_shp circle(x, y, rad, col);
		add_circle(circle);
	}

	template<typename... Circles>
	void Figure::add_circle(const Circle_shp& circle,
							const Circles& ... circles)
	{
		add_circle(circle);
		add_circle(circles...);
	}

	void Figure::add_line(const Line_shp& line)
	{
		Shape_ptr shape = std::make_shared<Line_shp>(line);
		shapes.push_back(shape);
		bounding_box.extend(line.get_bounding_box());
	}

	void Figure::add_line(const Coordinate& a,
						  const Coordinate& b,
						  const Coordinate& c,
						  Color col)
	{
		Line_shp line(a, b, c, col);
		add_line(line);
	}

	void Figure::add_line(const Segment_obj& segment,
						  Color col)
	{
		Line_shp line(segment, col);
		add_line(line);
	}

	void Figure::add_line(const Point_obj& point1,
						  const Point_obj& point2,
						  Color col)
	{
		Line_shp line(point1, point2, col);
		add_line(line);
	}

	void Figure::add_line(const Coordinate& x1,
						  const Coordinate& y1,
						  const Coordinate& x2,
						  const Coordinate& y2,
						  Color col)
	{
		Line_shp line(x1, y1, x2, y2, col);
		add_line(line);
	}

	template<typename... Lines>
	void Figure::add_line(const Line_shp& line,
						  const Lines& ... lines)
	{
		add_line(line);
		add_line(lines...);
	}

	void Figure::add_vertical_line(const Coordinate& x,
								   Color col)
	{
		Line_shp line(1, 0, -x, col);
		add_line(line);
	}

	void Figure::add_horizontal_line(const Coordinate& y,
									 Color col)
	{
		Line_shp line(0, 1, -y, col);
		add_line(line);
	}

	void Figure::add_text(const Text_shp& text)
	{
		Shape_ptr shape = std::make_shared<Text_shp>(text);
		shapes.push_back(shape);
		bounding_box.extend(text.get_bounding_box());
	}

	void Figure::add_text(const std::string& text,
						  const Coordinate& x,
						  const Coordinate& y,
						  unsigned size,
						  float off_x,
						  float off_y,
						  Color col)
	{
		Text_shp txt(text, x, y, size, off_x, off_y, col);
		add_text(txt);
	}

	void Figure::add_text(const std::string& text,
						  const Point_shp& point,
						  unsigned size,
						  Color col)
	{
		Text_shp txt(text, point, size, col);
		add_text(txt);
	}

	void Figure::add_text(const std::string& text,
						  const Segment_shp& segment,
						  unsigned size,
						  Color col)
	{
		Text_shp txt(text, segment, size, col);
		add_text(txt);
	}

	void Figure::add_text(const std::string& text,
						  const Vector_shp& vector,
						  unsigned size,
						  Color col)
	{
		Text_shp txt(text, vector, size, col);
		add_text(txt);
	}

	void Figure::merge_figure(const Figure& other)
	{
		for (unsigned i = 0; i < other.nb_shapes(); ++i)
		{
			shapes.push_back(other[i]);
		}
		bounding_box.extend(other.bounding_box);
	}

	template<typename... Figures>
	void Figure::merge_figure(const Figure& figure,
							  const Figures& ... figures)
	{
		merge_figure(figure);
		merge_figure(figures...);
	}

	void Figure::erase_last_shape()
	{
		if (is_empty())
		{
			return;
		}
		Coordinate xM = shapes.back()->get_bounding_box().get_max_abscissa();
		Coordinate xm = shapes.back()->get_bounding_box().get_min_abscissa();
		Coordinate yM = shapes.back()->get_bounding_box().get_max_ordinate();
		Coordinate ym = shapes.back()->get_bounding_box().get_min_ordinate();

		if (xM == get_max_abscissa() || xm == get_min_abscissa() ||
			yM == get_max_ordinate() || ym == get_min_ordinate())
		{
			need_remake_bounding_box = true;
		}

		shapes.pop_back();
	}

	void Figure::erase_last_k_shapes(unsigned int k)
	{
		if (k >= nb_shapes())
		{
			clear();
			return;
		}
		for (unsigned i = 0; i < k; ++i)
		{
			erase_last_shape();
		}
	}

	void Figure::make_bounding_box()
	{
		if (need_remake_bounding_box)
		{
			bounding_box.clear();
			for (unsigned i = 0; i < nb_shapes(); ++i)
			{
				bounding_box.extend(shapes[i]->get_bounding_box());
			}
		}
	}

	void Figure::clear()
	{
		shapes.clear();
		bounding_box.clear();
	}

	unsigned Figure::nb_shapes() const
	{ return shapes.size(); }

	bool Figure::is_empty() const
	{ return nb_shapes() == 0; }

	const Shape_ptr& Figure::operator[](unsigned int i) const
	{ return shapes[i]; }

	std::istream& operator>>(std::istream& is,
							 Figure& figure)
	{
		figure.clear();
		std::string shape_name;
		Point_shp point;
		Segment_shp segment;
		Line_shp line;
		Circle_shp circle;
		Polygon_shp polygon;
		Vector_shp vector;
		Text_shp text;

		while (!is.eof())
		{
			is >> shape_name;
			if (shape_name == POINT_NAME)
			{
				is >> point;
				figure.add_point(point);
			}
			else if (shape_name == SEGMENT_NAME)
			{
				is >> segment;
				figure.add_segment(segment);
			}
			else if (shape_name == LINE_NAME)
			{
				is >> line;
				figure.add_line(line);
			}
			else if (shape_name == CIRCLE_NAME)
			{
				is >> circle;
				figure.add_circle(circle);
			}
			else if (shape_name == POLYGON_NAME)
			{
				is >> polygon;
				figure.add_polygon(polygon);
			}
			else if (shape_name == VECTOR_NAME)
			{
				is >> vector;
				figure.add_vector(vector);
			}
			else if (shape_name == TEXT_NAME)
			{
				is >> text;
				figure.add_text(text);
			}
			shape_name = "";
		}
		return is;
	}
}