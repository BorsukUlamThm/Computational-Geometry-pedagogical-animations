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
	class Double_edge_shp : public Shape
	{
	private:
		Segment_obj edge;
		Color arrow1_color = DEFAULT_SHAPE_COLOR; // arrow from ogn to dst
		Color arrow2_color = DEFAULT_SHAPE_COLOR; // arrow from dst to ogn
		Color vertices_color = DEFAULT_SHAPE_COLOR;

	public:
		// standard constructors
		Double_edge_shp();
		Double_edge_shp(const Coordinate& ogn_x,
						const Coordinate& ogn_y,
						const Coordinate& dst_x,
						const Coordinate& dst_y,
						Color arrow1_col = DEFAULT_SHAPE_COLOR,
						Color arrow2_col = DEFAULT_SHAPE_COLOR,
						Color vertices_col = DEFAULT_SHAPE_COLOR);
		Double_edge_shp(const Double_edge_shp& other);

		//other constructor
		Double_edge_shp(const Point_obj& ogn,
						const Point_obj& dst,
						Color arrow1_col = DEFAULT_SHAPE_COLOR,
						Color arrow2_col = DEFAULT_SHAPE_COLOR,
						Color vertices_col = DEFAULT_SHAPE_COLOR);

		~Double_edge_shp() = default;

		Point_obj get_origin() const;
		Point_obj get_destination() const;
		Color get_arrows_color() const;
		Color get_vertices_color() const;

		void draw(Canvas& canvas) const override;
		void write(std::ostream& os) const override;

	public:
		friend std::istream& operator>>(std::istream& is,
										Double_edge_shp& double_edge);
	};

	std::ostream& operator<<(std::ostream& os,
							 const Double_edge_shp& double_edge);
	std::istream& operator>>(std::istream& is,
							 Double_edge_shp& double_edge);
}