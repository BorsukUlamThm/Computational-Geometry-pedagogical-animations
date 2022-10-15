#pragma once

#include "Shape.h"


namespace graphics
{
	/*!
	 * A Double_edge_shp is a pair of half edges drawn on a Canvas\n
	 * It is defined by\n
	 *
	 * - Two Point_shp that represents its vertices\n
	 * - The color of the two arrows between them on the Canvas\n
	 */
	class Half_edge_shp : public Shape
	{
	private:
		Segment_obj arrow;
		Color arrow_color = DEFAULT_SHAPE_COLOR;
		Color vertices_color = DEFAULT_SHAPE_COLOR;

	public:
		// standard constructors
		Half_edge_shp();
		Half_edge_shp(const Coordinate& ogn_x,
					  const Coordinate& ogn_y,
					  const Coordinate& dst_x,
					  const Coordinate& dst_y,
					  Color arrow_col = DEFAULT_SHAPE_COLOR,
					  Color vertices_col = DEFAULT_SHAPE_COLOR);
		Half_edge_shp(const Half_edge_shp& other);

		//other constructor
		Half_edge_shp(const Point_obj& ogn,
					  const Point_obj& dst,
					  Color arrow_col = DEFAULT_SHAPE_COLOR,
					  Color vertices_col = DEFAULT_SHAPE_COLOR);

		~Half_edge_shp() = default;

		Point_obj get_origin() const;
		Point_obj get_destination() const;
		Color get_arrow_color() const;
		Color get_vertices_color() const;

		void draw(Canvas& canvas) const override;
		void write(std::ostream& os) const override;

	public:
		friend std::istream& operator>>(std::istream& is,
										Half_edge_shp& double_edge);
	};

	std::ostream& operator<<(std::ostream& os,
							 const Half_edge_shp& double_edge);
	std::istream& operator>>(std::istream& is,
							 Half_edge_shp& double_edge);
}