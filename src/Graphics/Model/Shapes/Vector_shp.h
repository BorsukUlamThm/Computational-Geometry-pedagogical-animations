#pragma once

#include "Segment_shp.h"


namespace graphics
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * A Vector_shp is a vector drawn on a Canvas\n
	 * It is defined by\n
	 *
	 * - The x y coordinates of its endpoints
	 * - The color of the vector on the canvas
	 */
	class Vector_shp : public Shape
	{
	private:
		Coordinate origin_x = 0;
		Coordinate origin_y = 0;
		Coordinate destination_x = 0;
		Coordinate destination_y = 0;
		Color color = DEFAULT_PLOT_COLOR;

	public:
		// standard constructors
		Vector_shp();
		Vector_shp(const Coordinate& ogn_x,
				   const Coordinate& ogn_y,
				   const Coordinate& dst_x,
				   const Coordinate& dst_y,
				   Color col = DEFAULT_PLOT_COLOR);
		Vector_shp(const Vector_shp& other);

		//other constructors
		/*!
		 * Constructs the segment whose endpoints are ogn and dst
		 */
		Vector_shp(const Point_shp& ogn,
				   const Point_shp& dst,
				   Color col = DEFAULT_PLOT_COLOR);
		/*!
		 * Constructs the segment whose endpoints are the segment's endpoints
		 */
		explicit Vector_shp(const Segment_shp& segment,
							Color col = DEFAULT_PLOT_COLOR);

		~Vector_shp() = default;

		Coordinate get_origin_x() const;
		Coordinate get_origin_y() const;
		Coordinate get_destination_x() const;
		Coordinate get_destination_y() const;
		Color get_color() const;

		void draw(Canvas& canvas) const override;

	private:
		void make_bounding_box();

	public:
		friend std::istream& operator>>(std::istream& is,
										Vector_shp& vector);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Vector_shp::Vector_shp()
	{
		make_bounding_box();
	}

	Vector_shp::Vector_shp(const Coordinate& ogn_x,
						   const Coordinate& ogn_y,
						   const Coordinate& dst_x,
						   const Coordinate& dst_y,
						   Color col)
	{
		origin_x = ogn_x;
		origin_y = ogn_y;
		destination_x = dst_x;
		destination_y = dst_y;
		color = col;

		make_bounding_box();
	}

	Vector_shp::Vector_shp(const Vector_shp& other) : Shape(other)
	{
		origin_x = Coordinate(other.origin_x);
		origin_y = Coordinate(other.origin_y);
		destination_x = Coordinate(other.destination_x);
		destination_y = Coordinate(other.destination_y);
		color = other.color;
	}

	Vector_shp::Vector_shp(const Point_shp& ogn,
						   const Point_shp& dst,
						   Color col)
	{
		origin_x = ogn.get_abscissa();
		origin_y = ogn.get_ordinate();
		destination_x = dst.get_abscissa();
		destination_y = dst.get_ordinate();
		color = col;

		make_bounding_box();
	}

	Vector_shp::Vector_shp(const Segment_shp& segment,
						   Color col)
	{
		origin_x = segment.get_origin().get_abscissa();
		origin_y = segment.get_origin().get_ordinate();
		destination_x = segment.get_destination().get_abscissa();
		destination_y = segment.get_destination().get_ordinate();
		color = col;

		make_bounding_box();
	}

	Coordinate Vector_shp::get_origin_x() const
	{ return origin_x; }

	Coordinate Vector_shp::get_origin_y() const
	{ return origin_y; }

	Coordinate Vector_shp::get_destination_x() const
	{ return destination_x; }

	Coordinate Vector_shp::get_destination_y() const
	{ return destination_y; }

	Color Vector_shp::get_color() const
	{ return color; }

	void Vector_shp::make_bounding_box()
	{
		Coordinate x_min = std::min(origin_x, destination_x);
		Coordinate x_max = std::max(origin_x, destination_x);
		Coordinate y_min = std::min(origin_y, destination_y);
		Coordinate y_max = std::max(origin_y, destination_y);

		bounding_box = Bounding_box(x_min, x_max, y_min, y_max);
	}

	std::ostream& operator<<(std::ostream& os,
							 const Vector_shp& vector)
	{
		os << VECTOR_NAME << " "
		   << vector.get_origin_x() << " "
		   << vector.get_origin_y() << " "
		   << vector.get_destination_x() << " "
		   << vector.get_destination_y();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Vector_shp& vector)
	{
		is >> vector.origin_x
		   >> vector.origin_y
		   >> vector.destination_x
		   >> vector.destination_y;
		return is;
	}
}