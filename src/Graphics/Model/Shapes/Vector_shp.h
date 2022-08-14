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
		Segment_obj vector;
		Color color = DEFAULT_SHAPE_COLOR;

	public:
		// standard constructors
		Vector_shp();
		Vector_shp(const Coordinate& ogn_x,
				   const Coordinate& ogn_y,
				   const Coordinate& dst_x,
				   const Coordinate& dst_y,
				   Color col = DEFAULT_SHAPE_COLOR);
		Vector_shp(const Vector_shp& other);

		//other constructors
		/*!
		 * Constructs the segment whose endpoints are ogn and dst
		 */
		Vector_shp(const Point_obj& ogn,
				   const Point_obj& dst,
				   Color col = DEFAULT_SHAPE_COLOR);
		/*!
		 * Constructs the segment whose endpoints are the segment's endpoints
		 */
		explicit Vector_shp(const Segment_obj& segment,
							Color col = DEFAULT_SHAPE_COLOR);

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
		bounding_box = Bounding_box(vector);
	}

	Vector_shp::Vector_shp(const Coordinate& ogn_x,
						   const Coordinate& ogn_y,
						   const Coordinate& dst_x,
						   const Coordinate& dst_y,
						   Color col)
	{
		vector.origin_x = ogn_x;
		vector.origin_y = ogn_y;
		vector.destination_x = dst_x;
		vector.destination_y = dst_y;
		color = col;
		bounding_box = Bounding_box(vector);
	}

	Vector_shp::Vector_shp(const Vector_shp& other) : Shape(other)
	{
		vector.origin_x = Coordinate(other.vector.origin_x);
		vector.origin_y = Coordinate(other.vector.origin_y);
		vector.destination_x = Coordinate(other.vector.destination_x);
		vector.destination_y = Coordinate(other.vector.destination_y);
		color = other.color;
	}

	Vector_shp::Vector_shp(const Point_obj& ogn,
						   const Point_obj& dst,
						   Color col)
	{
		vector = Segment_obj(ogn, dst);
		color = col;
		bounding_box = Bounding_box(vector);
	}

	Vector_shp::Vector_shp(const Segment_obj& segment,
						   Color col)
	{
		vector = Segment_obj(segment);
		color = col;
		bounding_box = Bounding_box(vector);
	}

	Coordinate Vector_shp::get_origin_x() const
	{ return vector.origin_x; }

	Coordinate Vector_shp::get_origin_y() const
	{ return vector.origin_y; }

	Coordinate Vector_shp::get_destination_x() const
	{ return vector.destination_x; }

	Coordinate Vector_shp::get_destination_y() const
	{ return vector.destination_y; }

	Color Vector_shp::get_color() const
	{ return color; }

	std::ostream& operator<<(std::ostream& os,
							 const Vector_shp& vector)
	{
		os << VECTOR_NAME << " "
		   << vector.get_origin_x() << " "
		   << vector.get_origin_y() << " "
		   << vector.get_destination_x() << " "
		   << vector.get_destination_y() << " "
		   << vector.get_color();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Vector_shp& vector)
	{
		is >> vector.vector.origin_x
		   >> vector.vector.origin_y
		   >> vector.vector.destination_x
		   >> vector.vector.destination_y
		   >> vector.color;
		return is;
	}
}