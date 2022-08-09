#pragma once

/** @cond */
#include <iostream>
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Polygon_plot.h"
#include "Circle_plot.h"
#include "Line_plot.h"
#include "Text_plot.h"


namespace gr
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	enum Plot_type
	{
		POINT_PLT,
		SEGMENT_PLT,
		VECTOR_PLT,
		POLYGON_PLT,
		CIRCLE_PLT,
		LINE_PLT,
		TEXT_PLT
	};

	/*!
	 * Wrapper class for all the plots
	 */
	class Plot
	{
	private:
		Plot_type plot_type;
		union
		{
			Point_plot u_point;
			Segment_plot u_segment;
			Vector_plot u_vector;
			Polygon_plot u_polygon;
			Circle_plot u_circle;
			Line_plot u_line;
			Text_plot u_text;
		};

	public:
		explicit Plot(Plot_type type);
		explicit Plot(const Point_plot& point);
		explicit Plot(const Segment_plot& segment);
		explicit Plot(const Vector_plot& vector);
		explicit Plot(const Polygon_plot& polygon);
		explicit Plot(const Circle_plot& circle);
		explicit Plot(const Line_plot& line);
		explicit Plot(const Text_plot& text);
		Plot(const Plot& other);
		~Plot();

		Plot_type type() const;
		Point_plot point() const;
		Segment_plot segment() const;
		Vector_plot vector() const;
		Polygon_plot polygon() const;
		Circle_plot circle() const;
		Line_plot line() const;
		Text_plot text() const;

		Coordinate get_min_abscissa() const;
		Coordinate get_max_abscissa() const;
		Coordinate get_min_ordinate() const;
		Coordinate get_max_ordinate() const;
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Plot::Plot(Plot_type type)
	{
		plot_type = type;
		switch(type)
		{
			case POINT_PLT:
				new (&u_point) Point_plot();
				break;
			case SEGMENT_PLT:
				new (&u_segment) Segment_plot();
				break;
			case VECTOR_PLT:
				new (&u_vector) Vector_plot();
				break;
			case POLYGON_PLT:
				new (&u_polygon) Polygon_plot();
				break;
			case CIRCLE_PLT:
				new (&u_circle) Circle_plot();
				break;
			case LINE_PLT:
				new (&u_line) Line_plot();
				break;
			case TEXT_PLT:
				new (&u_text) Text_plot();
				break;
		}
	}

	Plot::Plot(const Point_plot& point):
			plot_type(POINT_PLT),
			u_point(Point_plot(point))
	{}

	Plot::Plot(const Segment_plot& segment):
			plot_type(SEGMENT_PLT),
			u_segment(Segment_plot(segment))
	{}

	Plot::Plot(const Vector_plot& vector):
			plot_type(VECTOR_PLT),
			u_vector(Vector_plot(vector))
	{}

	Plot::Plot(const Polygon_plot& polygon):
			plot_type(POLYGON_PLT),
			u_polygon(Polygon_plot(polygon))
	{}

	Plot::Plot(const Circle_plot& circle):
			plot_type(CIRCLE_PLT),
			u_circle(Circle_plot(circle))
	{}

	Plot::Plot(const Line_plot& line):
			plot_type(LINE_PLT),
			u_line(Line_plot(line))
	{}

	Plot::Plot(const Text_plot& text):
			plot_type(TEXT_PLT),
			u_text(Text_plot(text))
	{}

	Plot::Plot(const Plot& other)
	{
		plot_type = other.plot_type;
		switch(plot_type)
		{
			case POINT_PLT:
				new (&u_point) Point_plot(other.u_point);
				break;
			case SEGMENT_PLT:
				new (&u_segment) Segment_plot(other.u_segment);
				break;
			case VECTOR_PLT:
				new (&u_vector) Vector_plot(other.u_vector);
				break;
			case POLYGON_PLT:
				new (&u_polygon) Polygon_plot(other.u_polygon);
				break;
			case CIRCLE_PLT:
				new (&u_circle) Circle_plot(other.u_circle);
				break;
			case LINE_PLT:
				new (&u_line) Line_plot(other.u_line);
				break;
			case TEXT_PLT:
				new (&u_text) Text_plot(other.u_text);
				break;
		}
	}

	Plot::~Plot()
	{
		switch(plot_type)
		{
			case POINT_PLT:
				u_point.~Point_plot();
				break;
			case SEGMENT_PLT:
				u_segment.~Segment_plot();
				break;
			case VECTOR_PLT:
				u_vector.~Vector_plot();
				break;
			case POLYGON_PLT:
				u_polygon.~Polygon_plot();
				break;
			case CIRCLE_PLT:
				u_circle.~Circle_plot();
				break;
			case LINE_PLT:
				u_line.~Line_plot();
				break;
			case TEXT_PLT:
				u_text.~Text_plot();
				break;
		}
	}

	Plot_type Plot::type() const
	{
		return plot_type;
	}

	Point_plot Plot::point() const
	{
		return u_point;
	}

	Segment_plot Plot::segment() const
	{
		return u_segment;
	}

	Vector_plot Plot::vector() const
	{
		return u_vector;
	}

	Polygon_plot Plot::polygon() const
	{
		return u_polygon;
	}

	Circle_plot Plot::circle() const
	{
		return u_circle;
	}

	Line_plot Plot::line() const
	{
		return u_line;
	}

	Text_plot Plot::text() const
	{
		return u_text;
	}

	Coordinate Plot::get_min_abscissa() const
	{
		switch(plot_type)
		{
			case POINT_PLT:
				return u_point.get_min_abscissa();
			case SEGMENT_PLT:
				return u_segment.get_min_abscissa();
			case VECTOR_PLT:
				return u_vector.get_min_abscissa();
			case POLYGON_PLT:
				return u_polygon.get_min_abscissa();
			case CIRCLE_PLT:
				return u_circle.get_min_abscissa();
			case LINE_PLT:
				return u_line.get_min_abscissa();
			case TEXT_PLT:
				return u_text.get_min_abscissa();
		}
		return 0;
	}

	Coordinate Plot::get_max_abscissa() const
	{
		switch(plot_type)
		{
			case POINT_PLT:
				return u_point.get_max_abscissa();
			case SEGMENT_PLT:
				return u_segment.get_max_abscissa();
			case VECTOR_PLT:
				return u_vector.get_max_abscissa();
			case POLYGON_PLT:
				return u_polygon.get_max_abscissa();
			case CIRCLE_PLT:
				return u_circle.get_max_abscissa();
			case LINE_PLT:
				return u_line.get_max_abscissa();
			case TEXT_PLT:
				return u_text.get_max_abscissa();
		}
		return 0;
	}

	Coordinate Plot::get_min_ordinate() const
	{
		switch(plot_type)
		{
			case POINT_PLT:
				return u_point.get_min_ordinate();
			case SEGMENT_PLT:
				return u_segment.get_min_ordinate();
			case VECTOR_PLT:
				return u_vector.get_min_ordinate();
			case POLYGON_PLT:
				return u_polygon.get_min_ordinate();
			case CIRCLE_PLT:
				return u_circle.get_min_ordinate();
			case LINE_PLT:
				return u_line.get_min_ordinate();
			case TEXT_PLT:
				return u_text.get_min_ordinate();
		}
		return 0;
	}

	Coordinate Plot::get_max_ordinate() const
	{
		switch(plot_type)
		{
			case POINT_PLT:
				return u_point.get_max_ordinate();
			case SEGMENT_PLT:
				return u_segment.get_max_ordinate();
			case VECTOR_PLT:
				return u_vector.get_max_ordinate();
			case POLYGON_PLT:
				return u_polygon.get_max_ordinate();
			case CIRCLE_PLT:
				return u_circle.get_max_ordinate();
			case LINE_PLT:
				return u_line.get_max_ordinate();
			case TEXT_PLT:
				return u_text.get_max_ordinate();
		}
		return 0;
	}
}
