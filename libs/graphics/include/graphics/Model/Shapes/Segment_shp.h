#pragma once

#include "Shape.h"


namespace graphics
{
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
		Segment_obj segment;
		Color line_color = DEFAULT_SHAPE_COLOR;
		Color endpoints_color = DEFAULT_SHAPE_COLOR;

	public:
		// standard constructors
		Segment_shp();
		Segment_shp(const Coordinate& ogn_x,
					const Coordinate& ogn_y,
					const Coordinate& dst_x,
					const Coordinate& dst_y,
					Color line_col = DEFAULT_SHAPE_COLOR,
					Color end_points_col = DEFAULT_SHAPE_COLOR);
		Segment_shp(const Segment_shp& other);

		//other constructor
		Segment_shp(const Point_obj& ogn,
					const Point_obj& dst,
					Color line_col = DEFAULT_SHAPE_COLOR,
					Color endpoints_col = DEFAULT_SHAPE_COLOR);

		~Segment_shp() = default;

		Coordinate get_origin_x() const;
		Coordinate get_origin_y() const;
		Coordinate get_destination_x() const;
		Coordinate get_destination_y() const;
		Color get_line_color() const;
		Color get_endpoints_color() const;

		void draw(Canvas& canvas) const override;
		void write(std::ostream& os) const override;

	public:
		friend std::istream& operator>>(std::istream& is,
										Segment_shp& segment);
	};

	std::ostream& operator<<(std::ostream& os,
							 const Segment_shp& segment);
	std::istream& operator>>(std::istream& is,
							 Segment_shp& segment);
}