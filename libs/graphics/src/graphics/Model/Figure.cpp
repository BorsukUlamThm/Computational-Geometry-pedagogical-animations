#include "graphics/Model/Figure.h"


namespace graphics
{
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

	void Figure::parse_shape(std::ifstream& ifs)
	{
		std::string shape_name;

		ifs >> shape_name;
		if (shape_name == POINT_NAME)
		{
			Point_shp point;
			ifs >> point;
			add_point(point);
			return;
		}
		if (shape_name == SEGMENT_NAME)
		{
			Segment_shp segment;
			ifs >> segment;
			add_segment(segment);
		}
		if (shape_name == LINE_NAME)
		{
			Line_shp line;
			ifs >> line;
			add_line(line);
		}
		if (shape_name == CIRCLE_NAME)
		{
			Circle_shp circle;
			ifs >> circle;
			add_circle(circle);
		}
		if (shape_name == POLYGON_NAME)
		{
			Polygon_shp polygon;
			ifs >> polygon;
			add_polygon(polygon);
		}
		if (shape_name == VECTOR_NAME)
		{
			Vector_shp vector;
			ifs >> vector;
			add_vector(vector);
		}
		if (shape_name == TEXT_NAME)
		{
			Text_shp text;
			ifs >> text;
			add_text(text);
		}
	}

	void Figure::load(const std::string& name)
	{
		std::filesystem::path data_dir = utils::get_data_directory();
		std::ifstream ifs(data_dir / ("saved_figures/" + name));

		do
		{
			parse_shape(ifs);
		} while (!ifs.eof());
	}

	void Figure::save(const std::string& name)
	{
		std::filesystem::path data_dir = utils::get_data_directory();
		std::ofstream ofs(data_dir / ("saved_figures/" + name));

		for (auto& shape : shapes)
		{
			shape->write(ofs);
			ofs << std::endl;
		}
	}

	unsigned Figure::nb_shapes() const
	{ return shapes.size(); }

	bool Figure::is_empty() const
	{ return nb_shapes() == 0; }

	const Shape_ptr& Figure::operator[](unsigned int i) const
	{ return shapes[i]; }
}