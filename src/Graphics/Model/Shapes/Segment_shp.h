#pragma once

#include "Point_shp.h"


namespace graphics
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * A Segment_shp is a segment drawn on a Canvas\n
	 * It is defined by\n
	 *
	 * - Two Point_shp that represents its endpoints\n
	 * - The color of the line between them on the Canvas\n
	 */
	class Segment_shp : public Shape
	{
	private:
		Point_shp origin;
		Point_shp destination;
		Color line_color = DEFAULT_SHAPE_COLOR;

	public:
		// standard constructors
		Segment_shp();
		Segment_shp(const Point_shp& ogn,
					const Point_shp& dst,
					Color line_col = DEFAULT_SHAPE_COLOR);
		Segment_shp(const Segment_shp& other);

		// other constructor
		/*!
		 * Constructs the segment whose endpoints are ogn and dst\n
		 * where ogn coordinate (ogn_x, ogn_y) and dst (dst_x, dst_y)
		 */
		Segment_shp(const Coordinate& ogn_x,
					const Coordinate& ogn_y,
					const Coordinate& dst_x,
					const Coordinate& dst_y,
					Color line_col = DEFAULT_SHAPE_COLOR,
					Color end_points_col = DEFAULT_SHAPE_COLOR);

		~Segment_shp() = default;

		Point_shp get_origin() const;
		Point_shp get_destination() const;
		Color get_line_color() const;

		void draw(Canvas& canvas) const override;

	private:
		void make_bounding_box();

	public:
		friend std::istream& operator>>(std::istream& is,
										Segment_shp& segment);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Segment_shp::Segment_shp()
	{
		make_bounding_box();
	}

	Segment_shp::Segment_shp(const Point_shp& ogn,
							 const Point_shp& dst,
							 Color line_col)
	{
		origin = Point_shp(ogn);
		destination = Point_shp(dst);
		line_color = line_col;

		make_bounding_box();
	}

	Segment_shp::Segment_shp(const Segment_shp& other) : Shape(other)
	{
		origin = Point_shp(other.origin);
		destination = Point_shp(other.destination);
		line_color = other.line_color;
	}

	Segment_shp::Segment_shp(const Coordinate& ogn_x,
							 const Coordinate& ogn_y,
							 const Coordinate& dst_x,
							 const Coordinate& dst_y,
							 Color line_col,
							 Color end_points_col)
	{
		origin = Point_shp(ogn_x, ogn_y, end_points_col);
		destination = Point_shp(dst_x, dst_y, end_points_col);
		line_color = line_col;

		make_bounding_box();
	}

	Point_shp Segment_shp::get_origin() const
	{ return origin; }

	Point_shp Segment_shp::get_destination() const
	{ return destination; }

	Color Segment_shp::get_line_color() const
	{ return line_color; }

	void Segment_shp::make_bounding_box()
	{
		bounding_box.clear();
		bounding_box.extend(origin.get_bounding_box());
		bounding_box.extend(destination.get_bounding_box());
	}

	std::ostream& operator<<(std::ostream& os,
							 const Segment_shp& segment)
	{
		os << SEGMENT_NAME << " "
		   << segment.get_origin() << " "
		   << segment.get_destination();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Segment_shp& segment)
	{
		std::string dummy;
		is >> dummy
		   >> segment.origin
		   >> dummy
		   >> segment.destination;
		return is;
	}
}