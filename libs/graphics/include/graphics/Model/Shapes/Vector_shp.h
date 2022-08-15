#pragma once

#include "Shape.h"


namespace graphics
{
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
		void write(std::ostream& os) const override;

	public:
		friend std::istream& operator>>(std::istream& is,
										Vector_shp& vector);
	};

	std::ostream& operator<<(std::ostream& os,
							 const Vector_shp& vector);
	std::istream& operator>>(std::istream& is,
							 Vector_shp& vector);
}