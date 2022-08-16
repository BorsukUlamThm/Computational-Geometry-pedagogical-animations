#pragma once

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include "Bounding_box.h"
#include "Shapes/Point_shp.h"
#include "Shapes/Segment_shp.h"
#include "Shapes/Vector_shp.h"
#include "Shapes/Polygon_shp.h"
#include "Shapes/Circle_shp.h"
#include "Shapes/Line_shp.h"
#include "Shapes/Text_shp.h"


namespace graphics
{
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
		void add_segment(const Point_obj& ogn,
						 const Point_obj& dst,
						 Color line_col = DEFAULT_SHAPE_COLOR,
						 Color endpoints_col = DEFAULT_SHAPE_COLOR);
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
		void add_vector(const Point_obj& ogn,
						const Point_obj& dst,
						Color col = DEFAULT_SHAPE_COLOR);
		void add_vector(const Coordinate& ogn_x,
						const Coordinate& ogn_y,
						const Coordinate& dst_x,
						const Coordinate& dst_y,
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
					  const Point_obj& point,
					  unsigned size,
					  Color col);
		void add_text(const std::string& text,
					  const Point_shp& point,
					  unsigned size = 16,
					  Color col = DEFAULT_SHAPE_COLOR);
		void add_text(const std::string& text,
					  const Segment_obj& segment,
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
		 * Updates the Bounding_box if needed
		 */
		void make_bounding_box();
		void clear();

		void load(const std::string& name);
		void save(const std::string& name);

		unsigned nb_shapes() const;
		bool is_empty() const;
		const Shape_ptr& operator[](unsigned i) const;

	private:
		void parse_shape(std::ifstream& ifs);
	};


	/// TEMPLATE FUNCTION DEFINITIONS

	template<typename... Figures>
	Figure::Figure(const Figure& figure,
				   const Figures& ... figures)
	{
		merge_figure(figure);
		merge_figure(figures...);
	}

	template<typename... Points>
	void Figure::add_point(const Point_shp& point,
						   const Points& ... points)
	{
		add_point(point);
		add_point(points...);
	}

	template<typename... Segments>
	void Figure::add_segment(const Segment_shp& segment,
							 const Segments& ... segments)
	{
		add_segment(segment);
		add_segment(segments...);
	}

	template<typename... Vectors>
	void Figure::add_vector(const Vector_shp& vector,
							const Vectors& ... vectors)
	{
		add_vector(vector);
		add_vector(vectors...);
	}

	template<typename... Polygons>
	void Figure::add_polygon(const Polygon_shp& polygon,
							 const Polygons& ... polygons)
	{
		add_polygon(polygon);
		add_polygon(polygons...);
	}

	template<typename... Circles>
	void Figure::add_circle(const Circle_shp& circle,
							const Circles& ... circles)
	{
		add_circle(circle);
		add_circle(circles...);
	}

	template<typename... Lines>
	void Figure::add_line(const Line_shp& line,
						  const Lines& ... lines)
	{
		add_line(line);
		add_line(lines...);
	}

	template<typename... Figures>
	void Figure::merge_figure(const Figure& figure,
							  const Figures& ... figures)
	{
		merge_figure(figure);
		merge_figure(figures...);
	}
}